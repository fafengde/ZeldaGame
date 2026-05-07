# ZeldaGame

基于 Unreal Engine 5.4 开发的第三人称动作冒险游戏项目，灵感来源于塞尔达传说系列。

## 项目概述

本项目是一个完整的塞尔达风格动作冒险游戏 Demo，目前已完成主菜单系统及相关功能模块，核心玩法正在持续开发中。

## 已实现功能

### 1. 主菜单系统

- 自定义 GameMode + HUD 架构，HUD 作为 UI 管理中枢统一控制各面板
- 主菜单入场动画，支持自定义播放速率
- 面板懒加载机制（首次需要时才创建 Widget 实例，避免不必要的内存开销）

### 2. 登录系统

- 账号 / 密码输入界面
- 基于 SaveGame 的本地账号记忆功能
- "记住密码"勾选框：勾选后自动保存账号密码到本地存档，下次打开自动填充
- 取消勾选时自动清除本地存档数据

### 3. 注册系统

- 注册界面 UI
- 发送验证码按钮冷却倒计时功能（默认 5 秒）
- 冷却期间按钮禁用，实时显示剩余秒数
- 基于 FTimerHandle 的定时器递归回调实现

### 4. 设置系统

- 设置面板框架，内嵌按键设置子组件
- 常规设置与按键设置的分页架构

### 5. 按键自定义重映射系统

- 从 DataTable 读取按键配置，动态生成按键列表到可滚动面板
- 使用 InputKeySelector 控件实现可视化按键捕获
- 按键冲突检测：选择新按键时自动遍历检查是否与其他功能键重复，重复则拒绝修改
- 自定义按键持久化存档：修改按键后自动保存，下次启动自动加载
- 一键重置所有按键到默认值，同步清除存档并刷新 UI

### 6. 音频 / 素材

- BGM 音效系统配置（SoundClass、SoundCue、SoundMix、SoundAttenuation）
- 自定义中文字体集成
- UI 材质（边框材质）
- 过场动画 / MediaPlayer 视频资源准备

## 技术栈

| 类别 | 技术 |
|------|------|
| 引擎 | Unreal Engine 5.4 |
| 编程语言 | C++ |
| 输入系统 | Enhanced Input |
| UI 框架 | UMG (Unreal Motion Graphics) |
| 数据驱动 | DataTable |
| 持久化存储 | SaveGame |
| 定时器 | FTimerHandle |

## 项目架构

```
Source/ZeldaGame/
├── GamePlay/MainMenu/             # 游戏逻辑层
│   ├── MainMenuGameMode           # 主菜单 GameMode
│   └── MainMenuHUD                # HUD 管理器，统一管理所有 UI 面板
├── UMG/MainMenu/                  # UI 控件层
│   ├── MainMenuUserWidget         # 主菜单界面（含入场动画）
│   ├── LoginUserWidget            # 登录面板
│   ├── RegisterUserWidget         # 注册面板
│   ├── SettingsUserWidget         # 设置面板
│   ├── KeySettingsWidget          # 按键设置面板
│   └── KeyInfoWidget              # 单行按键信息控件
└── Data/                          # 数据层
    ├── Account/AccountSaveGame    # 账号存档数据
    └── KeyMapping/CustomKeyMapping # 按键映射存档数据
```

## 开发计划

### 第一阶段：角色控制
- [ ] 第三人称角色移动（跑、跳、冲刺、闪避翻滚）
- [ ] Spring Arm 相机系统（碰撞检测、延迟跟随）
- [ ] Enhanced Input 完整绑定

### 第二阶段：动画系统
- [ ] Animation Blueprint 状态机（Idle / Walk / Run / Jump / Fall）
- [ ] Blend Space 多方向移动混合
- [ ] Anim Montage 攻击 / 翻滚动作
- [ ] Anim Notify 攻击判定帧事件

### 第三阶段：战斗系统
- [ ] 轻攻击 / 重攻击连招系统
- [ ] 伤害框架（ApplyDamage / TakeDamage）
- [ ] 武器碰撞检测
- [ ] 受击反馈（顿帧、击退、镜头震动）
- [ ] 锁定目标系统

### 第四阶段：AI 敌人
- [ ] Behavior Tree + Blackboard 驱动的敌人 AI
- [ ] AI Perception 感知系统（视觉 / 听觉）
- [ ] NavMesh 导航寻路
- [ ] 2-3 种小怪 + 1 个 Boss

### 第五阶段：系统串联
- [ ] Interface 交互系统
- [ ] 道具拾取 / 背包系统
- [ ] 战斗 UI（血条、伤害数字、Boss 血条）
- [ ] 关卡设计与流程串联（主菜单 → 游戏关卡 → Boss 战）

### 第六阶段：打磨
- [ ] Niagara 粒子特效（武器拖尾、受击火花）
- [ ] 音效完善（攻击、受击、脚步、环境音）
- [ ] 材质效果（受击闪白、死亡溶解）
- [ ] 存档系统扩展（游戏进度存档）

## 环境要求

- Unreal Engine 5.4
- Visual Studio 2022 或 Rider
- Windows 10/11

## 构建与运行

1. 使用 UE5.4 打开 `ZeldaGame.uproject`
2. 编译 C++ 代码（Development Editor 配置）
3. 打开 `Content/ZeldaGame/Map/MainMenuMap` 地图
4. 点击运行即可体验主菜单功能
