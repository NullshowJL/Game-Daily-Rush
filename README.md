# 天天酷跑 | Daily Rush

> 本项目基于我在大学期间完成的一次项目作业，仅用于展示个人技术能力。请勿将本代码用于课程作业提交或其他学术用途。如需参考，请注明出处。

> This project is based on an assignment I completed during my university studies. It is intended solely to showcase my technical capabilities. Please do not use this code for course submissions or other academic purposes. If you wish to reference it, proper attribution is required.

---

## 项目概览 | Project Overview

**技术栈 | Tech Stack**：C++ + raylib

**项目亮点 | Project Highlights**：

- 实现了多层背景的自动滚动效果，增强视觉动感

  Implemented multi-layer background auto-scrolling to enhance visual dynamism

- 编写了敌人AI逻辑，包括移动、碰撞判定与触发机制

  Developed enemy AI logic, including movement, collision detection, and trigger mechanisms

- 设计并实现了本地排行榜系统，记录玩家得分

  Designed and built a local leaderboard system to record player scores

- 使用文本文件进行数据存储与读取

  Utilized text files for data storage and retrieval

---

## 核心玩法 | Core Gameplay

- 玩家控制角色以跳跃的方式躲避敌人

  Players control a character that avoids enemies by jumping

- 有三种难度的敌人：蜗牛、野猪和蜜蜂，它们具有不同的伤害值，玩家每躲开一个可以获得相应的分数

  There are three types of enemies with increasing difficulty: snails, boars, and bees. Each has a different damage value, and players earn points for successfully dodging them

- 玩家初始HP为100，成功达到终点时赢得游戏；如果途中玩家HP小于0则为输

  Players start with 100 HP. Reaching the goal with HP above 0 results in a win; if HP drops below 0 during the run, the game is lost

- 玩家在开始游戏前输入自己的名字，游戏结束后可查看游戏排行榜，其中会显示分数最高的5名玩家

  Before starting, players enter their name. After the game ends, a local leaderboard displays the top 5 scores

---

## 操作说明 | Controls

- 开始菜单 | Start Menu

  - 按 ”G/g“ 键进入游戏

    Press **G/g** to enter the game

  - 输入3个字母的名称，按”回车键“确定后开始游戏

  - Enter a three-letter name and press **Enter** to begin

- 游戏场景 | Gameplay Scene：

  - 按”空格键“跳起，可以躲避敌人

    Press **Spacebar** to jump and avoid enemies

  - 游戏途中按”P/p“键可以暂停游戏，再次按”P/p“键则继续游戏

    Press **P/p** during gameplay to pause; press again to resume

  - 游戏结束后，按”B/b“键显示分数排行榜

    After the game ends, press **B/b** to view the score leaderboard

---

## 快速开始 | Getting Started

### 中文说明：

1. 使用 Visual Studio 2022 打开项目解决方案文件（`.sln`）或新建空项目并导入源码  
2. 选择“Release”或“Debug”模式，点击“本地 Windows 调试器”运行项目  

### English Instructions:

1. Open the `.sln` solution file in Visual Studio 2022, or create a new project and import the source files  
2. Select "Release" or "Debug" mode and run the project using "Local Windows Debugger"  




