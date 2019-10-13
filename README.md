
# spring

A LONG TRIP.

## TODO:

- test matrix4x4/transform
    - transform local coordinate system

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

## spring engine real-time screenshot

-   diffuse material without shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_01.PNG)
