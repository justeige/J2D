Level = {

	-- IDs:
	AID_Truck = "truck-image",
	AID_Tank = "tank-image",
	AID_Jungle = "tilemap-image",
	AID_Tile_Map = "tilemap-image",
	AID_Chopper = "chopper-image",
	AID_Radar = "radar-image",
	AID_Bullet = "bullet-image",
	AID_Tree = "tree-image",
	AID_Charriot_Font = "charriot-font",
	AID_Pico8_5_Font = "pico-font-5",
	AID_Pico8_10_Font = "pico-font-10",

	-- asset table:
	assets = {
		[0] =
		{ type = "texture", id = AID_Tank, file = "./assets/images/tank-panther-right.png" },
		{ type = "texture", id = AID_Truck, file = "./assets/images/truck-ford-right.png" },
		{ type = "texture", id = AID_Chopper, file = "./assets/images/chopper-spritesheet.png" },
		{ type = "texture", id = AID_Radar, file = "./assets/images/radar.png" },
		{ type = "texture", id = AID_Bullet, file = "./assets/images/bullet.png" },
		{ type = "texture", id = AID_Tree, file = "./assets/images/tree.png" },
		{ type = "font", id = AID_Charriot_Font, file = "./assets/fonts/charriot.ttf", font_size = 14 },
		{ type = "font", id = AID_Pico8_5_Font, file = "./assets/fonts/pico8-font-5.ttf", font_size = 5 },
		{ type = "font", id = AID_Pico8_10_Font, file = "./assets/fonts/pico8-font-10.ttf", font_size = 10 }
	},

	-- tilemap:
	tilemap = {
		map_file = "./assets/tilemaps/jungle.map",
		texture_asset_id = "tilemap-texture",
		num_rows = 20,
		num_cols = 25,
		tile_size = 32,
		scale = 2.0
	},

	-- entities:
	entities = {
        [0] =
        {
            -- Player
            tag = "player",
            components = {
                transform = {
                    position = { x = 242, y = 110 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                rigidbody = {
                    velocity = { x = 0.0, y = 0.0 }
                },
                sprite = {
                    texture_asset_id = "chopper-texture",
                    width = 32,
                    height = 32,
                    z_index = 4,
                    fixed = false,
                    src_rect_x = 0,
                    src_rect_y = 0
                },
                animation = {
                    num_frames = 2,
                    speed_rate = 10 -- fps
                },
                boxcollider = {
                    width = 32,
                    height = 25,
                    offset = { x = 0, y = 5 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 200, y = 200 },
                    projectile_duration = 10, -- seconds
                    repeat_frequency = 0, -- seconds
                    hit_percentage_damage = 10,
                    friendly = true
                },
                keyboard_controller = {
                    up_velocity = { x = 0, y = -50 },
                    right_velocity = { x = 50, y = 0 },
                    down_velocity = { x = 0, y = 50 },
                    left_velocity = { x = -50, y = 0 }
                },
                camera_follow = {
                    follow = true
                }
            }
        },
        {
            -- Tank
            group = "enemies",
            components = {
                transform = {
                    position = { x = 200, y = 497 },
                    scale = { x = 1.0, y = 1.0 },
                    rotation = 0.0, -- degrees
                },
                sprite = {
                    texture_asset_id = "tank-texture",
                    width = 32,
                    height = 32,
                    z_index = 2
                },
                boxcollider = {
                    width = 25,
                    height = 18,
                    offset = { x = 0, y = 7 }
                },
                health = {
                    health_percentage = 100
                },
                projectile_emitter = {
                    projectile_velocity = { x = 100, y = 0 },
                    projectile_duration = 2, -- seconds
                    repeat_frequency = 1, -- seconds
                    hit_percentage_damage = 20,
                    friendly = false
                }
            }
        }
    }
}