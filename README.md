# ROS2 AI 开发学习工作空间

基于 ROS2 Jazzy 的 AI 机器人开发练习仓库，用于记录从基础节点到 AI 感知能力接入的学习过程。

## 环境要求

- Ubuntu 24.04
- ROS2 Jazzy
- Python 3.12
- colcon

确认环境：

```bash
echo $ROS_DISTRO   # 期望输出 jazzy
```

## 工作空间结构

```text
ros2_ws_for_learning/
├── src/                  # 源码（唯一需要提交的目录）
│   └── my_package/       # ament_python 示例包
├── build/                # 构建中间产物（gitignore）
├── install/              # 安装结果（gitignore）
└── log/                  # 构建日志（gitignore）
```

## 快速开始

```bash
# 1. 编译工作空间
cd ~/ros2_ws_for_learning
colcon build

# 2. source 环境
source /opt/ros/jazzy/setup.bash
source install/setup.bash

# 3. 运行示例节点
ros2 run my_package my_node
ros2 run my_package my_node_1004_1
```

## 学习路线

### 阶段一：ROS2 基础

- [x] 创建 ament_python 包
- [x] 注册 console_scripts 入口点
- [x] `ros2 run` / `ros2 node` / `ros2 topic` 常用命令
- [ ] Publisher / Subscriber 话题通信
- [ ] Service / Client 服务通信
- [ ] Action 长任务通信
- [ ] 参数（Parameters）与 launch 文件

### 阶段二：AI 能力接入

- [ ] 图像话题接入（`sensor_msgs/Image` + cv_bridge）
- [ ] 目标检测节点（YOLO / ONNX Runtime）
- [ ] 语义分割与深度估计
- [ ] 大语言模型（LLM）服务节点
- [ ] 视觉语言模型（VLM，如问答、场景描述）
- [ ] 语音识别（ASR）与语音合成（TTS）

### 阶段三：机器人智能闭环

- [ ] 感知结果发布为自定义消息
- [ ] 行为决策节点（规则引擎 / LLM Agent）
- [ ] 导航与避障联动（Nav2）
- [ ] 机械臂抓取（MoveIt2 + 视觉定位）
- [ ] 多传感器融合与时间同步

## ROS2 + AI 典型架构

```text
传感器驱动 ──> 感知节点(YOLO/VLM) ──> /detection ──> 决策节点(LLM)
     │                                              │
     └──────────────────────────────────────────────┴──> 控制节点 ──> 底盘/机械臂
```

核心思路：**每个 AI 能力封装为独立 ROS2 节点**，通过话题或服务交互，方便单独替换模型、独立调优性能。

## 常用调试命令

```bash
ros2 node list                     # 查看活跃节点
ros2 topic list                    # 查看话题
ros2 topic echo /topic_name        # 查看话题数据
rqt_graph                          # 节点关系图
ros2 bag record -a                 # 录制全部话题数据
colcon test --packages-select my_package
```

## 备注

- `build/`、`install/`、`log/` 已通过 `.gitignore` 忽略，不纳入版本管理。
- 新增 Python 节点后，记得在 `setup.py` 的 `entry_points` 中注册入口。
