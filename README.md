git add README.md

git rebase --continue

# G6 — Cross-Platform Game Asset Pipeline & Resource Management Framework

> **Object-Oriented Programming (OOP) Project — C++**
> A resource management framework that simulates how modern games efficiently load, share, cache, and dispose of game assets.

---

## 📌 Overview

In a large-scale game, especially an open-world game, thousands of objects may share the same resources such as **textures, meshes, and audio files**.

Naively loading and storing every resource independently can lead to:

* Excessive RAM/VRAM consumption
* Long startup and loading times
* Duplicated resources
* Inefficient resource management
* Difficulty synchronizing assets between different game systems

For example, if 5,000 trees each store their own 4 MB texture, the game could theoretically consume:

```text
5,000 × 4 MB = 20 GB
```

Instead of storing the same texture repeatedly, our project introduces a centralized **Asset Pipeline & Resource Management Framework**.

The system focuses on three core problems:

| Problem                         | Solution            |
| ------------------------------- | ------------------- |
| Duplicated asset data           | **Flyweight** |
| Unnecessary / early loading     | **Proxy**     |
| Distributed resource management | **Singleton** |

These three patterns form the core architecture of the project.

---

# 🎯 Project Objectives

The main objectives of this project are:

* Apply the four fundamental principles of **Object-Oriented Programming**
* Implement and understand **Flyweight, Proxy, and Singleton**
* Demonstrate practical resource management techniques
* Reduce unnecessary memory consumption
* Implement lazy loading for game assets
* Centralize asset management
* Manage asset lifetime safely using smart pointers
* Measure the performance impact of different resource management strategies
* Build an extensible architecture that can support additional features

---

# 🧩 OOP Concepts

The project applies the four major OOP principles directly to the asset management problem.

### 1. Abstraction

The `IAsset` interface defines the common operations that every asset must provide:

```cpp
Load()
Unload()
GetMemoryUsage()
GetId()
```

Concrete asset types such as `TextureAsset` and `AudioAsset` implement this interface.

This allows the system to work with assets through a common abstraction instead of depending on specific asset classes.

---

### 2. Encapsulation

Internal asset data such as:

* Pixel buffers
* Loading state
* Resource information

is hidden inside the corresponding classes.

External components interact with assets through public methods rather than directly accessing their internal data.

---

### 3. Inheritance

Concrete asset classes inherit from the common `IAsset` interface:

```text
             IAsset
             /    \
            /      \
 TextureAsset    AudioAsset
```

This allows different asset types to be handled consistently.

---

### 4. Polymorphism

The system can store different asset types through a base-class interface:

```cpp
std::vector<IAsset*>
```

For example:

```text
IAsset*
 ├── TextureAsset
 └── AudioAsset
```

Calling:

```cpp
asset->Load();
```

can execute the appropriate implementation depending on the actual asset type.

---

# 🏗️ System Architecture

The core architecture follows this flow:

```text
                  Client
                    │
                    ▼
            ┌─────────────────┐
            │  AssetManager   │
            │    Singleton    │
            └────────┬────────┘
                     │
                     ▼
            ┌─────────────────┐
            │   AssetProxy    │
            │      Proxy      │
            └────────┬────────┘
                     │
                     ▼
          ┌──────────────────────┐
          │  FlyweightFactory    │
          │   Shared Asset Pool  │
          └──────────┬───────────┘
                     │
          ┌──────────┴──────────┐
          ▼                     ▼
   TextureAsset            AudioAsset
```

The three required patterns have different responsibilities:

### Singleton — AssetManager

Provides one centralized entry point for managing assets.

```text
Client
  │
  ▼
AssetManager::Instance()
```

The project uses a **Meyers' Singleton** implementation with:

* Private constructor
* Static `Instance()`
* Deleted copy constructor
* Deleted assignment operator

---

### Proxy — AssetProxy

`AssetProxy` represents an asset without immediately loading the real resource.

```text
Client
   │
   ▼
AssetProxy
   │
   │ Load() requested
   ▼
Real Asset
```

This enables **lazy loading**.

Creating a proxy does not necessarily mean that the actual asset data is loaded into memory.

---

### Flyweight — FlyweightFactory

The Flyweight pattern allows multiple game objects to share the same intrinsic asset data.

For example:

```text
Tree #1 ─┐
Tree #2 ─┤
Tree #3 ─┼──► Shared Tree Texture
Tree #4 ─┤
Tree #5 ─┘
```

Instead of creating multiple copies of the same texture, the system stores one shared copy inside the Flyweight pool.

The project specifically separates:

* **Intrinsic state** — shared data such as texture/pixel data
* **Extrinsic state** — information specific to each object

This reduces unnecessary memory consumption.

---

# 💾 Memory Management

The project uses C++ smart pointers, particularly:

```cpp
std::shared_ptr
```

instead of manually managing resources with:

```cpp
new
delete
```

Reference counting is used to determine whether an asset is still being used.

The garbage collection mechanism can identify resources where:

```cpp
use_count() == 1
```

meaning only the Flyweight pool still owns the resource.

Such resources can then be unloaded and removed from the pool.

---

# 🚀 Extended Features

Beyond the three required Design Patterns, the project includes several additional features designed to make the system more realistic and extensible.

## 1. LRU Cache

### Problem

A game may continuously move between many different worlds or areas.

Previously loaded assets may remain in memory even when they are no longer frequently used.

### Solution

We implement an **LRU (Least Recently Used) Cache** using:

```text
unordered_map + list
```

When the cache exceeds its configured limit, the least recently used asset can be evicted.

Example:

```text
World 1 → World 5 → World 10 → World 3 → World 20
   │         │          │          │
   └─────────┴──────────┴──────────┴──► LRU Cache
```

This helps control memory usage when many assets are accessed over time.

---

# ⚡ 2. Asynchronous Loading

Synchronous loading can block the main thread when loading large assets.

The project therefore introduces asynchronous loading using:

```cpp
std::async
```

or:

```cpp
std::thread
```

The loading process can run independently from the main thread.

The asset lifecycle is represented using:

```cpp
enum class LoadState {
    NotLoaded,
    Loading,
    Ready
};
```

The client can check the asset state and only use the asset after it reaches:

```text
Ready
```

The goal is to demonstrate that the main thread can continue operating while a heavy asset is being loaded.

---

# 👁️ 3. Observer Pattern

After introducing asynchronous loading, other systems need a way to know when an asset has finished loading.

The project therefore adds an `IAssetListener` interface:

```cpp
OnAssetLoaded(id)
```

For example:

```text
AssetProxy
    │
    │ Asset Loaded
    ▼
IAssetListener
    │
    ▼
LoadingUI
```

This allows a UI system to receive notifications without continuously polling the asset state.

Example:

```text
Progress bar:
World 20 ready!
```

This demonstrates how the architecture can be extended with an additional design pattern without breaking the original three-pattern architecture.

---

# 📊 Benchmark

To evaluate the effectiveness of the architecture, the project compares three scenarios:

### Scenario 1 — Naive Implementation

```text
No Flyweight
No Proxy
```

### Scenario 2 — Shared Resources

```text
Flyweight
No Proxy
```

### Scenario 3 — Full Resource Management

```text
Flyweight
+
Proxy
+
LRU Cache
```

The benchmark measures:

* Total memory usage
* Initial startup/loading time
* Asset loading time when changing worlds

The results are presented using tables and/or charts.

---

# 🎮 Scene Simulator

The project includes a console-based **Scene Simulator** that demonstrates how the asset pipeline works in a simulated game environment.

The simulator can create hundreds of objects such as:

```text
🌳 Trees
👾 Enemies
🧍 NPCs
```

and simulate movement between different areas.

During the simulation, the system logs events such as:

```text
[LOAD]       Texture_Tree.png
[CACHE HIT]  Texture_Tree.png
[LOADING]    World_20
[EVICT]      World_03
[DISPOSE]    Texture_Old.png
```

This makes the resource management process easier to observe during the final presentation.

---

# 🧪 Testing

The project includes unit tests covering the core functionality.

Examples include:

### Singleton Test

Verify that different calls return the same `AssetManager` instance.

```cpp
&AssetManager::Instance()
```

should return the same address.

### Proxy Test

Creating a proxy should not immediately load the actual asset.

```text
Create Proxy
     │
     ▼
No Asset Loaded
     │
     ▼
Load()
     │
     ▼
Asset Loaded
```

### Flyweight Test

Multiple objects requesting the same texture should reference the same shared resource.

### Garbage Collection Test

After all proxies release an asset, garbage collection should remove unused resources.

### LRU Test

When the cache exceeds its limit, the least recently used asset should be evicted.

---

# 📁 Project Structure

A possible project structure is:

```text
G6-Asset-Pipeline/
│
├── include/
│   ├── IAsset.h
│   ├── TextureAsset.h
│   ├── AudioAsset.h
│   ├── AssetProxy.h
│   ├── AssetManager.h
│   ├── FlyweightFactory.h
│   ├── LRUCache.h
│   └── IAssetListener.h
│
├── src/
│   ├── TextureAsset.cpp
│   ├── AudioAsset.cpp
│   ├── AssetProxy.cpp
│   ├── AssetManager.cpp
│   ├── FlyweightFactory.cpp
│   ├── LRUCache.cpp
│   └── ...
│
├── tests/
│   └── ...
│
├── benchmark/
│   └── ...
│
├── demo/
│   └── SceneSimulator.cpp
│
├── docs/
│   ├── UML/
│   └── report/
│
├── README.md
└── CMakeLists.txt
```

> The exact directory structure may change according to the implementation of the team.

---

# 🛠️ Technologies

| Technology                       | Purpose                        |
| -------------------------------- | ------------------------------ |
| **C++**                    | Main programming language      |
| **OOP**                    | Core programming paradigm      |
| **Smart Pointers**         | Resource lifetime management   |
| **STL**                    | Data structures and containers |
| `unordered_map`                | Fast asset lookup              |
| `list`                         | LRU ordering                   |
| `std::async` / `std::thread` | Asynchronous loading           |
| Catch2 /`assert()`             | Unit testing                   |
| PlantUML / draw.io               | UML diagrams                   |
| Valgrind / AddressSanitizer      | Memory leak detection          |

---

# 📐 Design Patterns Used

| Pattern             | Role in Project                          |
| ------------------- | ---------------------------------------- |
| **Singleton** | Centralized`AssetManager`              |
| **Proxy**     | Lazy loading of assets                   |
| **Flyweight** | Sharing intrinsic asset data             |
| **Observer**  | Asset loading notifications              |
| **LRU Cache** | Automatic eviction of rarely used assets |

The first three patterns are the **mandatory patterns** of the assignment; Observer and LRU are extensions implemented to improve the system's extensibility and resource management.

---

# 🔄 Overall Workflow

The complete asset request flow can be summarized as:

```text
                    Client
                       │
                       ▼
              AssetManager
               (Singleton)
                       │
                       ▼
                AssetProxy
                  (Proxy)
                       │
                  Load()
                       │
                       ▼
             FlyweightFactory
                       │
             ┌─────────┴─────────┐
             ▼                   ▼
       Existing Asset       New Asset
             │                   │
             └─────────┬─────────┘
                       ▼
                  Asset Pool
                       │
                       ▼
                   LRU Cache
                       │
                       ▼
                 Asset Ready
                       │
                       ▼
                 Scene / UI
```

---

# 📈 Expected Results

The project aims to demonstrate that:

* Multiple objects can share the same asset data.
* Assets do not need to be loaded before they are actually used.
* Resource management can be centralized through a single manager.
* Smart pointers can simplify resource lifetime management.
* Unused assets can be automatically removed from memory.
* Heavy assets can be loaded asynchronously.
* Other systems can receive notifications when assets become ready.
* Benchmarking can provide measurable evidence of the impact of different architectures.

The project therefore connects OOP and Design Patterns to a realistic systems problem instead of implementing the patterns only as isolated examples.

---

# 👥 Team

**Group G6**

| Member | Responsibility |
| ------ | -------------- |
| Thịnh | TBD            |
| Quang  | TBD            |
| Minh   | TBD            |
| Tú    | TBD            |
| Mạnh  | TBD            |

> Team responsibilities can be updated as the implementation progresses.

---

# 📚 Documentation

The repository will contain:

* UML Class Diagram
* Architecture documentation
* Benchmark results
* Test cases
* Project report
* Presentation slides

---

# ✅ Final Checklist

* [ ] `IAsset` + concrete asset classes implemented
* [ ] Polymorphism demonstrated
* [ ] Singleton implemented and tested
* [ ] Proxy implemented with lazy loading
* [ ] Flyweight implemented with shared resource pool
* [ ] Reference counting / smart pointers implemented
* [ ] Garbage collection implemented
* [ ] LRU Cache implemented
* [ ] Asynchronous loading implemented
* [ ] Observer notification implemented
* [ ] Benchmark completed
* [ ] Scene Simulator completed
* [ ] UML diagram completed
* [ ] Unit tests completed
* [ ] Memory leak checked
* [ ] Final report completed
* [ ] Presentation slides completed

---

# 🎓 Academic Purpose

This project is developed as part of the **Object-Oriented Programming (OOP)** course.

The main purpose is to demonstrate the practical application of:

```text
OOP Principles
      +
Design Patterns
      +
Resource Management
      +
Performance Measurement
      +
Software Architecture
```

rather than implementing Design Patterns as isolated theoretical examples.

=======
x1

OOP

# OOP

>>>>>>> f79ec89 ( pull readme from github)
>>>>>>>
>>>>>>
>>>>>
>>>>
>>>
>>
