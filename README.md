
# spring

A LONG LONG LONG , VERY LONG TRIP.

## TODO: 2020.03.11

- memory optimization

    - refactor frambufferobject module
        - customize color format
        - enable anti-aliasing
        - enable depth/stencil buffer
        - enable minmaps
        - set wrap mode and filter mode
  
- renderer core

    - complete the node system
    - pbr supports all type lights
    - add lambert / half lambert lighting model shader program
    - fix the shadow system

- extension

    - scene serialize **(40%)**
        - support to serialize mesh object reference
        - support to serialize textures reference
    - scene deserialize
    - scene editor gizmos
        - drag
        - scale
        - rotate

## TODO: 2020.02.14

- particle system
    - particle renderer core **(Finished)**
    - physical motion simulate **(Finished)**
    - life circle control **(Finished)**
    - 2d mode

- graphic core
    - refactor graphic apis to graphic setting.
    - camera supports hdr mode

- refactor 
    - mesh / material / shader / meshrenderer
    - defragment scripts directory (**Finished,use vcpkg manage the third-party libraries**)
    - use uniform buffer to optimize uniform data

## TODO: 2020.01.09

- physisc-based rendering system
    - support all types of lights(directional light/spot light/point light)
    - support all types of texture
    
- support multi rendering mode 
    - forward rendering mode
    - deferred rendering mode

- build spring engine **(Finished build version , release version failed.)**

- shader system 
    - independent shader compiler
        - support compiling in runtime(recompileing shader and replacing running shader instance)
        - add error shader , replace shader that encountering error when compiling shader by error shader **(Finished)**
    - support time type(such as unity shader)**(Finished)**

## TODO: 2019.12.09

- immediate mode graphic user interface
    - integration dear imgui **(Finished)**
    - spring engine editor basic windows
        - scene window **(Basic edition Finished)**
        - inspector window
            - transform tree node **(Finished)**
            - mateiral tree node (pbr mateiral inspector node) **(Finished)**

- input system upgrade (replaced window api by glfw library , glfw is a cross platform library) **(Finished)**

- pick system
    - pick base on gpu pick;
    - integrate bullet physics engine or PhysX to implement pick base on physics
    - pick base on ray-obb

## TODO: 2019.11.10

- shadow system
    - support all type lights
        - directional light **(Finised)**
        - spot light
        - point light

    - shadow type
        - hard shadow **(Finished)**
        - soft shadow **(Finished)**

    - evironment shadow setting **(Finished)**

- post processing system **(10%)**
    - bloom **(Finished)**
    - anti-aliasing **(replaced MSAA by post processing anti-aliasing)**
    - ambient occlusion
    - color correction
    - tone mapping **(Finished)**
    - outline 

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

-   postprocessing(bloom) and postprocessing editor window

    ![editor window](/screenshot/spring%20engine%20realtime%20screenshot_07.jpg)

-   particle
    
    ![alpha test error](/screenshot/spring%20engine%20realtime%20screenshot_06.jpg)

-   pbr
    
    ![ibl_with_antialiasing](/screenshot/spring%20engine%20realtime%20screenshot_05.png)

-   ibl
    
    ![ibl_without_antialiasing](/screenshot/spring%20engine%20realtime%20screenshot_04.jpg)

-   diffuse material without shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_01.PNG)

-   diffuse material with shadow
    
    ![diffuse](/screenshot/spring%20engine%20realtime%20screenshot_02.jpg)

-   pbr(basic version)
    
    ![pbr_without_antialiasing](/screenshot/spring%20engine%20realtime%20screenshot_03.png)