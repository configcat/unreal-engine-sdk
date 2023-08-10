# Contributing to the ConfigCat SDK for Unreal Engine

ConfigCat SDK is an open source project. Feedback and contribution are welcome. Contributions are made to this repo via Issues and Pull Requests.

## Submitting bug reports and feature requests

The ConfigCat SDK team monitors the [issue tracker](https://github.com/configcat/unreal-engine-sdk/issues) in the SDK repository. Bug reports and feature requests specific to this SDK should be filed in this issue tracker. The team will respond to all newly filed issues.

## Submitting pull requests

We encourage pull requests and other contributions from the community. 
- Before submitting pull requests, ensure that all temporary or unintended code is removed.
- Be accompanied by a complete Pull Request template (loaded automatically when a PR is created).

When you submit a pull request or otherwise seek to include your change in the repository, you waive all your intellectual property rights, including your copyright and patent claims for the submission. For more details please read the [contribution agreement](https://github.com/configcat/legal/blob/main/contribution-agreement.md).

In general, we follow the ["fork-and-pull" Git workflow](https://github.com/susam/gitpr)

1. Fork the repository to your own Github account
2. Clone the project to your machine
3. Create a branch locally with a succinct but descriptive name
4. Commit changes to the branch
5. Following any formatting and testing guidelines specific to this repo
6. Push changes to your fork
7. Open a PR in our repository and follow the PR template so that we can efficiently review the changes.

## Build instructions

This SDK is a wrapper around the [CPP-SDK](https://github.com/configcat/cpp-sdk) to expose the functionality inside Unreal Engine Blueprints & C++.

### Prerequisites

To **contribute** the ConfigCat SDK for Unreal Engine, you will need to have:
1. Install Unreal Engine either via [official release](https://docs.unrealengine.com/5.2/en-US/installing-unreal-engine/) or a [source built](https://docs.unrealengine.com/5.2/en-US/building-unreal-engine-from-source/)
1. Install the [C++ Prequistes](https://docs.unrealengine.com/5.1/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/) required for Unreal Engine 
1. Create a **C++ based** [project](https://docs.unrealengine.com/5.2/en-US/creating-a-new-project-in-unreal-engine/)

Optionally: complete the platform specific set-up,e.g.: [iOS](https://docs.unrealengine.com/5.0/en-US/setting-up-an-unreal-engine-project-for-ios/), [Android](https://docs.unrealengine.com/5.0/en-US/android-support-for-unreal-engine/), [Linux](https://docs.unrealengine.com/5.0/en-US/linux-game-development-in-unreal-engine/) or other platform you might target.

### Install the plugin

To install you have to complete the following steps:
1. Create a `Plugins` folder inside your root folder
1. Clone the repository inside your `Plugins` folder using: `git clone https://github.com/configcat/unreal-engine-sdk`
1. Start the Unreal Editor
1. Enable the **ConfigCat** plugin using the [Enabling a plugin](https://docs.unrealengine.com/5.1/en-US/working-with-plugins-in-unreal-engine/) steps
1. Regenerate your project files and recompile your project

### Using the Plugin

The plugin functionality can be accessed inside Unreal Engine by leveraging the `UConfigCatSubsystem`.

Either via C++: 
```
const FString MyValue = UConfigCatSubsystem::Get()->GetStringValue(TEXT("MyKey"), TEXT(""), {});
UE_LOG(LogTemp, Warning, TEXT("%s"), *MyValue);
```

Or via Blueprints:

TODO

## Advanced usage

### Building a custom CPP-SDK

If you need to change or test core functionality of the SDK, you might need to rebuild the `.lib` or `.a` loaded by the plugin.

The easiest way to achieve this is to use [vcpkg](https://github.com/microsoft/vcpkg) with the `--editable` flag.

#### Setup

- On Windows:
  ```cmd
  git clone https://github.com/microsoft/vcpkg
  .\vcpkg\bootstrap-vcpkg.bat
  ```

- On Linux/Mac:
  ```bash
  git clone https://github.com/microsoft/vcpkg
  ./vcpkg/bootstrap-vcpkg.sh
  ```

Optionally you can use one of the Dockerfiles inside [build-environments](https://github.com/outoftheboxplugins/configcat-unreal/tree/main/Extras/build-environments) to get all the prequistes for certain platform pre-installed.

#### Installing

Depending on your target platform, you might want to use a specific [triplet](https://learn.microsoft.com/en-us/vcpkg/users/triplets). If you are unusure what triplet you need to use, you can check the [build CPP-SDK action](https://github.com/outoftheboxplugins/configcat-unreal/blob/main/.github/workflows/update-cpp-sdk.yml) and copy the `--triplet XXX` part.


for instance to build the `.a` for android, you will need to run:

`./vcpkg/vcpkg install configcat --editable --triplet arm64-android`


#### Modifying the source

After installing you can navigate to the ConfigCat source: `/vcpkg/buildtrees/configcat/src/vX.Y.Z-COMMIT/` (e.g.: `/vcpkg/buildtrees/configcat/src/v3.0.0-da9db9971a`) and modify the source as you need.

#### Rebuilding

To force vcpkg to rebuild your changes run:
  ```
  ./vcpkg/vcpkg install remove configcat --triplet arm64-android
  ./vcpkg/vcpkg install configcat --editable --triplet arm64-android
  ```

NOTE: replace `arm64-android` with your triplet as needed.

#### Updating the lib

After rebuilding you will need to copy the resuling `.lib` or `.a` files built by vcpkg into the plugin.

You can find the new binaries inside:
- On Windows: `/vcpkg/installed/arm64-android/lib/`
- On Linux/Mac: `/vcpkg/installed/arm64-android/configcat/lib`