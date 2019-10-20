
# spring

A LONG TRIP.

## TODO:

- test spring engine mathf library
    - transform local coordinate system
    - quaternion moudle.

- orbit camera 
    - zoom
    - pan
    - rotate with a point

- load .fbx / .obj / .gltf model, use spring engine diffuse shader.
    - supports directional light
    - supports spot light
    - supports point light
    - specualr
    - supports transparency (fade/cutto mode)

- 2d text rendering 
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

- distance between orbit camera and target can not less than zero.
- keep the size of axis helper the same ,whereever camera is

## spring engine real-time screenshot

-   diffuse material without shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_01.PNG)
