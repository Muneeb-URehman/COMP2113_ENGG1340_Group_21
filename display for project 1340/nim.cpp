#ifndef NIM_CPP
#define NIM_CPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <stdexcept>
#include <algorithm>
#include "display.h"
#include <ncursesw/ncurses.h>

using StateAction = std::pair<std::vector<int>, std::pair<int, int>>;

Display* display = Display::instance();
class Nim {
private:
    std::vector<int> piles;
    int player;     // 0 or 1: whose turn it is
    int winner;     // -1 = no winner yet; 0 or 1 = that player won

    //Display* display = Display::instance();

public:
    Nim(const std::vector<int>& initial)
        : piles(initial), player(0), winner(-1) {
    }

    // Return all legal actions (pile index, count to remove)
    static std::set<std::pair<int, int>> available_actions(const std::vector<int>& piles) {
        std::set<std::pair<int, int>> actions;
        for (int i = 0; i < (int)piles.size(); i++) {
            for (int j = 1; j <= piles[i]; j++) {
                actions.insert({ i, j });
            }
        }
        return actions;
    }

    // Return the other player
    static int other_player(int pl) {
        return pl == 0 ? 1 : 0;
    }

    // Switch the current player
    void switch_player() {
        player = other_player(player);
    }

    // Make a move; if the board is empty *after* switching, that switched‐to player wins
    void move(const std::pair<int, int>& action) {
        int pile = action.first;
        int count = action.second;
        if (winner != -1)
            display->error("Game already won");
        if (pile < 0 || pile >= (int)piles.size())
            display->error("Invalid pile");
        if (count < 1 || count > piles[pile])
            display->error("Invalid number of objects");

        // Remove objects
        piles[pile] -= count;

        // Switch turn
        switch_player();

        // If board empty, the *new* current player is the winner
        if (std::all_of(piles.begin(), piles.end(),
            [](int x) { return x == 0; })) {
            winner = player;
        }
    }

    // Accessors
    const std::vector<int>& get_piles() const { return piles; }
    int get_player()            const { return player; }
    int get_winner()            const { return winner; }
    bool game_over()            const { return winner != -1; }
};

class NimAI {
private:
    double alpha, epsilon;
    std::map<StateAction, double> q;
    std::mt19937 rng;

    // Internal Q‐value updater
    void update_q_value(const std::vector<int>& state,
        const std::pair<int, int>& action,
        double old_q,
        double reward,
        double future_rewards)
    {
        double target = reward + future_rewards;
        q[{state, action}] = old_q + alpha * (target - old_q);
    }

public:
    NimAI(double alpha = 0.5, double epsilon = 0.1)
        : alpha(alpha), epsilon(epsilon), rng(std::random_device{}()) {
    }

    // Return Q(s, a)
    double get_q_value(const std::vector<int>& state,
        const std::pair<int, int>& action) const
    {
        auto it = q.find({ state, action });
        return it == q.end() ? 0.0 : it->second;
    }

    // Return max_a' Q(s', a')
    double best_future_reward(const std::vector<int>& state) {
        double best = 0.0;
        for (auto& a : Nim::available_actions(state)) {
            best = std::max(best, get_q_value(state, a));
        }
        return best;
    }

    // Q‐learning update step
    void update(const std::vector<int>& old_state,
        const std::pair<int, int>& action,
        const std::vector<int>& new_state,
        double reward)
    {
        double old_q = get_q_value(old_state, action);
        double future_q = best_future_reward(new_state);
        update_q_value(old_state, action, old_q, reward, future_q);
    }

    std::pair<int, int> choose_action(const std::vector<int>& state, bool use_epsilon = true) {
        auto actions_set = Nim::available_actions(state);
        std::vector<std::pair<int, int>> actions(actions_set.begin(), actions_set.end());

        std::pair<int, int> best_action = actions[0];
        double best_q = get_q_value(state, best_action);
        for (auto& a : actions) {
            double qv = get_q_value(state, a);
            if (qv > best_q) {
                best_q = qv;
                best_action = a;
            }
        }


        if (!use_epsilon) {
            return best_action;
        }

        std::uniform_real_distribution<double> prob(0.0, 1.0);
        if (prob(rng) < epsilon) {
            std::uniform_int_distribution<int> dist(0, actions.size() - 1);
            return actions[dist(rng)];
        }

        return best_action;
    }
};

// Train by self-play, using the “last” bookkeeping from your Python code
NimAI train(int n_games, const std::vector<int>& map) {
    NimAI player;
    for (int i = 0; i < n_games; i++) {
        Nim game(map);

        std::vector<int> last_state[2];
        std::pair<int, int> last_action[2];
        bool has_last[2] = { false, false };

        while (!game.game_over()) {
            int pl = game.get_player();
            auto state = game.get_piles();
            auto action = player.choose_action(state, true);

            last_state[pl] = state;
            last_action[pl] = action;
            has_last[pl] = true;

            game.move(action);
            auto new_state = game.get_piles();

            if (game.game_over()) {
                player.update(state, action, new_state, -1.0);
                int winner = game.get_winner();
                if (has_last[winner]) {
                    player.update(last_state[winner], last_action[winner], new_state, +1.0);
                }
            }
            else {
                int curr = game.get_player();
                if (has_last[curr]) {
                    player.update(last_state[curr], last_action[curr], new_state, 0.0);
                }
            }
        }
    }
    display->print("Done training");
    return player;
}

void play(NimAI& ai, const std::vector<int>& map) {
    Nim game(map);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> coin(0, 1);
    int human_player = coin(rng);

    while (!game.game_over()) {
        std::cout << "\nPiles:\n";
        auto piles = game.get_piles();
        for (int i = 0; i < (int)piles.size(); i++) {
            std::cout << "  Pile " << i << ": " << piles[i] << "\n";
        }

        int pl = game.get_player();
        std::pair<int, int> action;
        auto actions = Nim::available_actions(piles);

        if (pl == human_player) {
            std::cout << "Your turn.\n";
            while (true) {
                int pile, count;
                std::cout << "  Choose pile: ";  std::cin >> pile;
                std::cout << "  Choose count: "; std::cin >> count;
                if (actions.count({ pile, count })) {
                    action = { pile, count };
                    break;
                }
                std::cout << "Invalid move. Try again.\n";
            }
        }
        else {
            action = ai.choose_action(piles, false);
            std::cout << "AI chose to take "
                << action.second
                << " from pile "
                << action.first
                << ".\n";
        }

        game.move(action);
    }

    int winner = game.get_winner();
    if (winner == human_player) {
        std::cout << "\nYou win!\n";
    }
    else {
        std::cout << "\nAI wins!\n";
    }
}
#endif