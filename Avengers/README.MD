## Avengers!!! Assemble...

Welcome to **Avengers Assemble**, a turn‑based puzzle game set in the Marvel Cinematic Universe. Select your favorite Avenger, outsmart Hawkeye (just like Black Widow did in the movie) and avoid picking up the last block, forcing Hawkeye to retrive the Soul Stone.

---

### 🎮 Game Overview

In **Avengers Assemble**, you and an AI‑controlled Hawkeye take turns removing blocks from a stack of pillars.

The twist? If Hawkeye is forced to take the final block, YOU WIN! Hawkeye retrives the Soul Stone and the main MCU Timeline remains untampered. This allows the main timeline to go as shown in the movie - "Avengers Endgame" - where the Avengers sucessfully stop Thanos.

However, if Hawkeye isn't the last one to take the final block, this changes the entire timeline as a new branch grows off when you grab the soul stone instead. As mentioned by Dr. Strange, there is only "ONE" possibility out of "14,000,605" that leads to Avengers stopping Thanos. Thus, the TVA appears to prunes you! Or shall I say - "Ah, the TVA in all its bureaucratic glory has graciously chosen to prune you with your own… ‘defeat.’ How utterly delightful.” (Loki - God of Time + God of Mischief)

Each match features:

* **Randomly determined turns**: Who starts each game? The choice is up to chance. ⚖️
* **Varied pillar configurations**: Every level has different number of blocks per pillar, keeping strategy fresh.
* **Dynamic difficulty**: Choose from *Easy*, *Medium*, or *Hard* — Hawkeye (AI) will adapt and become savvier as you climb the difficulty ladder.

---

### 🦸 Character Roster

| Character                    
| ---------------------------- 
| Iron Man ⚛️   
| Black Panther 👑
| Hulk 🟢🦾
| Wolverine ⚔️
| Deadpool 🔴
| Falcon 🪽

*\*Hawkeye is an AI that is your opponent.*

---

### ⚙️ How to Play

1. **Main Menu**

   * **Start**: Launch a new game.
   * **About**: Read instructions.
   * **Exit**: Quit the game.
   * Navigate with **↑ ↓** and select with **Enter**.

2. **Choose Difficulty**

   * Pick **Easy**, **Medium**, or **Hard**.
   * Confirm with **Enter**.

3. **Select Level (1–10)**

   * Each level brings a new pillar arrangement.
   * Move **↑ ↓ ← →**, then press **Enter**.

4. **Pick Your Avenger**

   * Six heroes appear; choose yours with **arrow keys**.
   * Press **Enter** to confirm.

5. **Gameplay**

   * Highlight a pillar with **← →**.
   * Select how many blocks to remove with **↑ ↓**.
   * Press **Enter** to execute your move.
   * After each turn, press **Enter** to see the updated board.

6. **Winning the Game**

   * Force Hawkeye to take the last block to claim victory!

---

### 🖥️ Installation & Execution

**Prerequisites**: A terminal size of at least **150×40** columns. Otherwise, you’ll see a prompt to enlarge your window.

1. **Upload**: Transfer the unzipped game folder to the HKU CS server using FileZilla (VPN required).
2. **Log in**: SSH into `cs.hku.hk` with your department credentials.
3. **Navigate**: `cd <project-folder>` (e.g., `cd 1340Project`).
4. **Set permissions**:

   ```bash
   chmod +x run.sh nim_game
   ```
5. **Run**:

   ```bash
   make run
   ```

---

### 🤖 AI Implementation

Our AI opponent, Hawkeye, uses **reinforcement learning** to refine its strategy with every match. Expect tougher, more adaptive gameplay the more you play!

### 📚 Dependencies

* **ncursesw**: Handles terminal graphics (ASCII art) and keyboard input for a smooth, immersive experience.

---

### 🏆 Credits

**Group 21 – ENGG1340 & COMP2113**

* Lohano Luv Kumar
* Nalluri Parjany
* Peng Zhenghui
* Rehman Mian Muhammad Muneeb-Ur
* Wang Aofei
* Wang Lixiao

Thank you for playing! May your strategy outshine Hawkeye’s precision.

---

*Make sure you don't annoy the TVA by causing a Nexus Event. Or else, you are destined to be snapped into particles by Thanos or pruned to the End of Time where Alioth shall feast upon you!*
