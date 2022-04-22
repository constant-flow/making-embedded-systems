# 3 microphone audio locator

## Concept

See the required components of the planned system [here](https://github.com/constant-flow/making-embedded-systems/tree/main/exercise_1)

## State Table

| **State**               | **Action**                          | **OUT:** Screen     | **IN:** Button / Long Press            | **IN:** Loud Sound Input | **IN:** Buffering Done |
| ----------------------- | ----------------------------------- | ------------------- | -------------------------------------- | ------------------------ | ---------------------- |
| `START`                 | Init, go to `TRACKING_2D_BUFFERING` |                     | –                                      | –                        | –                      |
| `TRACKING_2D_BUFFERING` | Clear calculated direction          | "Make a loud noise" | –                                      | –                        | `TRACKING_2D_NO_HIT`   |
| `TRACKING_3D_BUFFERING` | Clear calculated direction          | "Make a loud noise" | –                                      | –                        | `TRACKING_3D_NO_HIT`   |
| `TRACKING_2D_NO_HIT`    |                                     |                     | `TRACKING_3D_NO_HIT`                   | `TRACKING_2D`            | –                      |
| `TRACKING_2D`           | Store calculated direction          | Show 2D direction   | `TRACKING_3D`, `TRACKING_2D_BUFFERING` | –                        | –                      |
| `TRACKING_3D_NO_HIT`    |                                     |                     | `TRACKING_2D_NO_HIT`                   | `TRACKING_3D`            | –                      |
| `TRACKING_3D`           | Store calculated direction          | Show 3D direction   | `TRACKING_2D`, `TRACKING_3D_BUFFERING` | –                        | –                      |