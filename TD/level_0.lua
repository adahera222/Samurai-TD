map_file = "test_map_0.tmx"
textures_file = "sword_testing.pvr.ccz"
frames_file = "sword_testing.plist"


num_spawn_point = 1


fighters_unlocked = {
    num_unlocked = 1,
    
    fighter_0 = 1,
}


towers_unlocked = {
    num_unlocked = 4,
    tower_0 = 0,
    tower_1 = 1,
    tower_2 = 2,
    tower_3 = 3,
}


---------------------------
-- Waves
---------------------------

num_waves = 1

wave_0 = {
    enemy_type = 1,
    enemy_num = 5,
    spawn_time_from_last_wave = 5,
    spawn_interval = 5,
    spawn_point = 0,
}

--[[
wave_1 = {
    enemy_type = 1,
    enemy_num = 5,
    spawn_time_from_last_wave = 20,
    spawn_interval = 0.6,
    spawn_point = 0,
}


wave_2 = {
    enemy_type = 2,
    enemy_num = 3,
    spawn_time_from_last_wave = 22,
    spawn_interval = 1.2,
    spawn_point = 0,
}
]]--