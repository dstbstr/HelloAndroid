# About
This is intended to be a starting point for creating an android app/game.

Technologies used:
* Android
* OpenGL
* Dear Imgui (for rendering a UI)
* stb-image (for decoding png/jpg)

# Building
Consider adding a file called SplashScreen.jpg to src/main/assets

## VsCode
### Extensions: 
* C/C++
* C/C++ Extension Pack
* C++ TestMate
* CMake Tools
* CMake
* CodeLLDB
* Android
* Android Debug
* Android iOS Emulator
* Android System Tools
* Logcat
* Gradle for Java

### Tasks
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Assemble Debug",
            "command": "./gradlew.bat",
            "type": "shell",
            "args": ["assembleDebug"],
            "problemMatcher": [
                "$tsc"
            ],
            "presentation": {
                "reveal": "always"
            },
            "group": {
                "kind": "build",
                "isDefault": true
            }
        },
        {
            "label": "Assemble Release",
            "command": "./gradlew.bat",
            "type": "shell",
            "args": ["assemble"],
            "problemMatcher": [
                "$tsc"
            ],
            "presentation": {
                "reveal": "always"
            },
            "group": "build"
        }
    ]
}
```

### Launch
```json
{
    "version": "0.2.0",
    "configurations" : [
        {
            "name" : "Android Launch",
            "type": "android-debug",
            "request": "launch",
            "target": "last-selected",
            "mode" : "native",
            "apkPath": "${workspaceFolder}/HelloAndroid/build/outputs/apk/debug/HelloAndroid-debug.apk",
            "launchActivity": "android.app.NativeActivity",
            "native" : {
				// note: this doesn't appear to work
                "symbolSearchPaths": [
                    "${workspaceFolder}/HelloAndroid/build/outputs/native-debug-symbols/debug/x86_64/",
                ],
            }

        }
    ]
}
```

# Native
This is a folder for cross-platform C++ code.  This is intended to be unit-testable/game-agnostic/platform-agnostic code.

## Core

### Service Locator
A global service locator which allows disparate parts of the application to inject cross-cutting concerns.  Said another way, it is intended to be the only global mutable state.  In its current form, ServiceLocator does not enforce single-ownership, so you'll have to do that.

```cpp
ServiceLocator::Get().CreateIfMissing<GameEngine>(); // creates a GameEngine for the ServiceLocator to own

// Elsewhere in the code
auto& gameEngine = ServiceLocator::Get().GetRequired<GameEngine>();

auto* maybeThere = ServiceLocator::Get().Get<MySharedClass>();
if(maybeThere) ...
```

The service locator also supports polymorphism.
```cpp
ServiceLocator::Get().SetThisAsThat<DefaultRandom, IRandom>();

IRandom& rand = ServiceLocator::Get().GetRequired<IRandom>();
```

Because the service locator owns the instances, it creates them when requested, so you can pass constructor args to the set/create methods.

```cpp
ServiceLocator::Get().Set<SomeClass>(aName, anId, aBoolFlag);
// internally calls SomeClass{aName, anId, aBoolFlag};
```

### PubSub
This is the event system.  This is another attempt at decoupling parts of the application, where publishers and subscribers don't need knowledge of each other.

```cpp
// Health subsystem
if(thePlayer.IsDead) {
	ServiceLocator::Get().GetRequired<PubSub<PlayerDeath>>().Publish(PlayerDeath{ thePlayer.Name });
}

// Achievement system
void OnPlayerDeath(const PlayerDeath& event) {
	// Unlock an anti-achievement, or prevent a clean-run achievement
}

ServiceLocator::Get().GetRequired<PubSub<PlayerDeath>>().Subscribe(OnPlayerDeath);
```

### Logging
To enable logging, we need to call Log::Initialize, and at some point create log sinks (things that respond to log events).
Because game developers are control freaks, logs aren't immediately written, but queued up (except for error messages.  Errors fire immediately and crash the app like they're supposed to).  Periodically the logs need to be flushed to see them.

```cpp
// early in main
StdOutLogWriter logWriter{LogFilter{}.WithLevel(Log::Level::Warn)};
Log::Initialize();
Log::Info("Logging initialized");

//main loop
while(true) {
	Game::Tick();
	Graphics::Tick();
	
	Log::Flush();
}
```
