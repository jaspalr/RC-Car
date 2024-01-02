add_executable(${ProjectName}
    main.c
    motor.c
    servo.c
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4
    hardware_gpio
	hardware_pwm 
    )

pico_add_extra_outputs(${ProjectName})