print("hello world");


---------------------------------------
            -- fighter 1 --
---------------------------------------

fighter_1 = {
    name = "Peasant",
    sprite_name = "sword_walk_0.png",
    type = 1,
    
    guarding_radius = 50,
    body_radius = 15,
    
    max_health = 70,
    speed_level = 2,
    }


fighter_1_behaviors = {
    num_of_behaviors = 1,
    
    behavior_0 = "walk",
}


fighter_1_walk = {
    name = "fighter_1_walk",
    num_of_frames = 3,
    
    frame_0 = "sword_walk_0.png",
    nums_of_frame_0 = 1,
    
    frame_1 = "sword_walk_1.png",
    nums_of_frame_1 = 1,
    
    frame_2 = "sword_walk_2.png",
    nums_of_frame_2 = 3,
}

