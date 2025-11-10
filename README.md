# 加速懸浮球小項目

本項目實現了一個基於 **Java + Smali + Native (C++)** 的懸浮球功能，並通過 **DobbyHook** 在 Native 層面對 Cocos2d-lua 和 Cocos2d-js 引擎進行精準 Hook，從而對游戲實現變速效果。

---

## 功能概述

- **Java 層**：實現懸浮球 UI 與交互邏輯
- **Smali 微調**：編譯後注入 Smali 代碼，橋接至 Native 層
- **C++ 層（核心）**：使用 [Dobby](https://github.com/jmpews/Dobby) 實現 Native Hook
  - 支持 **Cocos2d-lua** 引擎
  - 支持 **Cocos2d-js** 引擎

---
