test = {
    myInt = 1,
    herInt = 2,
    myDouble = 1.30,
    }

tower_0 = {
    name = "EmptyTower",
    sprite_name = "empty_tower.png",
    resource_needed = 0,

    num_upgrades = 1,
    upgrade0 = 1,
    
    attack_interval = 0,
    projectile_type = 0,
    
    guarding_radius = 0,
    body_radius = 20,
    
    description = "Empty land that can be built on",
    };

tower_1 = {
    name = "ArcherTower",
    sprite_name = "archer_tower.png",
    resource_needed = 70,
    
    num_upgrades = 1,
    upgrade0 = 2,
    
    guarding_radius = 80,
    body_radius = 25,
    
    attack_interval = 1.0,
    projectile_type = 1,
    
    description = "Basic attack unit",
    };
    
    
tower_2 = {
    name = "ArcherTowerLv2",
    sprite_name = "archer_tower_2.png",
    resource_needed = 110,
    
    num_upgrades = 1,
    upgrade0 = 3,
    
    guarding_radius = 100,
    body_radius = 25,
    
    attack_interval = 1.0,
    projectile_type = 1,

    description = "Stronger power, and faster shooting",
    
    };
    
    
tower_3 = {
    name = "ArcherTowerLv3",
    sprite_name = "archer_tower.png",
    resource_needed = 160,
    
    num_upgrades = 0,
    
    attack_interval = 1.0,
    projectile_type = 1,
    
    guarding_radius = 120,
    body_radius = 25,

    description = "Much stronger power, and much faster shooting",
    };