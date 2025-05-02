#ifndef NIM_H
#define NIM_H

#include <vector>
#include <set>
#include <map>
#include <utility>
#include <random>

using StateAction = std::pair<std::vector<int>, std::pair<int, int>>;

class Nim {
private:
    std::vector<int> piles;
    int player;
    int winner;

public:
    explicit Nim(const std::vector<int>& initial);

    static std::set<std::pair<int, int>> available_actions(const std::vector<int>& piles);
    static int other_player(int pl);

    void switch_player();
    void move(const std::pair<int, int>& action);

    const std::vector<int>& get_piles() const;
    int get_player() const;
    int get_winner() const;
    bool game_over() const;
};

class NimAI {
private:
    double alpha;
    double epsilon;
    std::map<StateAction, double> q;
    std::mt19937 rng;

    void update_q_value(const std::vector<int>& state,
                        const std::pair<int, int>& action,
                        double old_q,
                        double reward,
                        double future_rewards);

public:
    explicit NimAI(double alpha = 0.5, double epsilon = 0.1);

    double get_q_value(const std::vector<int>& state, const std::pair<int, int>& action) const;
    double best_future_reward(const std::vector<int>& state);
    void update(const std::vector<int>& old_state,
                const std::pair<int, int>& action,
                const std::vector<int>& new_state,
                double reward);

    std::pair<int, int> choose_action(const std::vector<int>& state, bool use_epsilon = true);
};

NimAI train(int n_games, const std::vector<int>& initial_piles);
void play(NimAI& ai, const std::vector<int>& initial_piles);

#endif
