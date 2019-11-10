
# spring

A LONG LONG LONG , VERY LONG TRIP.

## TODO: 2019.11.10

- shadow system
    - support all type lights
        - directional light **(Finised)**
        - spot light
        - point light

    - shadow type
        - hard shadow
        - soft shadow

    - evironment shadow setting

- post processing system
    - bloom
    - anti-aliasing
    - ambient occlusion
    - color correction

## TODO: before 2019.11.10

- test spring engine mathf library
    - transform local coordinate system
    - quaternion moudle.

- orbit camera 
    - zoom **(Finised)**
    - pan
    - rotate with a point **(Finised)**

- load .fbx / .obj / .gltf model, use spring engine diffuse shader.
    - supports directional light **(Finised)**
    - supports spot light **(Finised)**
    - supports point light **(Finised)**
    - specualr **(Finised)**
    - supports transparency (fade/cutto mode) **(Finised)**

- 2d text rendering **(important)**
    - supports chinese.

- scene serialize and deserialize (JSON format and binary format.)
    - scene serialize
        - engine environment setting
        - objects
            - lights
            - 3d models
    - scene deserialize
        - engine environment setting
        - objects
            - lights
            - 3d models




    
## ISSUES

### 2019.11.10

- spring engine shader class does not support multi texture2d

### before 2019.11.10

- distance between orbit camera and target can not less than zero. **(Finised)**
- keep the size of axis helper the same ,whereever camera is **(Finised)**

## spring engine real-time screenshot

-   diffuse material without shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_01.PNG)

-   diffuse material with shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_02.jpg)
