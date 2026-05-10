# C 語言做貪食蛇小遊戲

# 預設前提
v1:
- only windows

v4:
- only windows & linux

# 架構原理
- **單執行緒同步遊戲迴圈 Single-Threaded Synchronous Game Loop**
- 記憶體配置
- 邏輯運算
- 渲染機制

// caution: may they init MAP[[]] by all zero value or could failed when editor or buffer unexpectable failure?
char MAP[X][Y] = {0};

v1:
> 使用最基本的 C 方法做出最基礎的貪食蛇遊戲。
- 阻塞式輸入 
- printf: input, scanf: output, system("cls"): refresh
- array: MAP[X: WIDTH][Y: HEIGHT]
- for: map render, while: game loop

v2:
- 非阻塞式輸入

v3:
- 使用 WIN32 API

v4