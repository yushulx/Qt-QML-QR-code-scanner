## How to Build the Shared Library
1. Replace `TEAM_ID` with your own.
2. Build the shared library for iOS:

    ```bash
    cmake -G Xcode ..
    cmake --build . --config release
    ```