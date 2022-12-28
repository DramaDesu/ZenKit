// Copyright © 2022 Luis Michaelis <lmichaelis.all+dev@gmail.com>
// SPDX-License-Identifier: MIT
#include <phoenix/vobs/trigger.hh>

namespace phoenix::vobs {
	void trigger::parse(trigger& obj, archive_reader& ctx, game_version version) {
		vob::parse(obj, ctx, version);
		obj.target = ctx.read_string();                // triggerTarget
		obj.flags = ctx.read_raw_bytes().get();        // flags
		obj.filter_flags = ctx.read_raw_bytes().get(); // filterFlags
		obj.vob_target = ctx.read_string();            // respondToVobName
		obj.max_activation_count = ctx.read_int();     // numCanBeActivated
		obj.retrigger_delay_sec = ctx.read_float();    // retriggerWaitSec
		obj.damage_threshold = ctx.read_float();       // damageThreshold
		obj.fire_delay_sec = ctx.read_float();         // fireDelaySec

		if (obj.saved) {
			// TODO: in save-games triggers behave differently
			(void) ctx.read_float(); // nextTimeTriggerable
			ctx.skip_object(false);
			(void) ctx.read_int(); // countCanBeActivated

			if (version == game_version::gothic_2) {
				(void) ctx.read_bool(); // isEnabled
			}
		}
	}

	void trigger_mover::parse(trigger_mover& obj, archive_reader& ctx, game_version version) {
		trigger::parse(obj, ctx, version);
		obj.behavior = static_cast<mover_behavior>(ctx.read_enum()); // moverBehavior
		obj.touch_blocker_damage = ctx.read_float();                 // touchBlockerDamage
		obj.stay_open_time_sec = ctx.read_float();                   // stayOpenTimeSec
		obj.locked = ctx.read_bool();                                // moverLocked
		obj.auto_link = ctx.read_bool();                             // autoLinkEnabled

		if (version == game_version::gothic_2) {
			obj.auto_rotate = ctx.read_bool(); // autoRotate
		}

		auto keyframe_count = ctx.read_word(); // numKeyframes
		if (keyframe_count > 0) {
			obj.speed = ctx.read_float();                                    // moveSpeed
			obj.lerp_mode = static_cast<mover_lerp_mode>(ctx.read_enum());   // posLerpType
			obj.speed_mode = static_cast<mover_speed_mode>(ctx.read_enum()); // speedType

			auto sample_reader = ctx.read_raw_bytes(); // keyframes

			for (int32_t i = 0; i < keyframe_count; ++i) {
				auto position = sample_reader.get_vec3();

				auto x = sample_reader.get_float();
				auto y = sample_reader.get_float();
				auto z = sample_reader.get_float();
				auto w = sample_reader.get_float();

				obj.keyframes.push_back(animation_sample {position, glm::quat {w, x, y, z}});
			}
		}

		if (obj.saved) {
			// TODO: in save-games movers behave differently
			(void) ctx.read_vec3();  // actKeyPosDelta
			(void) ctx.read_float(); // actKeyframeF
			(void) ctx.read_int();   // actKeyframe
			(void) ctx.read_int();   // nextKeyframe
			(void) ctx.read_float(); // moveSpeedUnit
			(void) ctx.read_float(); // advanceDir
			(void) ctx.read_enum();  // moverState
			(void) ctx.read_int();   // numTriggerEvents
			(void) ctx.read_float(); // stayOpenTimeDest
		}

		obj.sfx_open_start = ctx.read_string();    // sfxOpenStart
		obj.sfx_open_end = ctx.read_string();      // sfxOpenEnd
		obj.sfx_transitioning = ctx.read_string(); // sfxMoving
		obj.sfx_close_start = ctx.read_string();   // sfxCloseStart
		obj.sfx_close_end = ctx.read_string();     // sfxCloseEnd
		obj.sfx_lock = ctx.read_string();          // sfxLock
		obj.sfx_unlock = ctx.read_string();        // sfxUnlock
		obj.sfx_use_locked = ctx.read_string();    // sfxUseLocked
	}

	void trigger_list::parse(trigger_list& obj, archive_reader& ctx, game_version version) {
		trigger::parse(obj, ctx, version);
		obj.mode = static_cast<trigger_batch_mode>(ctx.read_enum()); // listProcess

		auto target_count = ctx.read_byte(); // numTarget
		for (int32_t i = 0; i < target_count; ++i) {
			obj.targets.emplace_back(target {
			    ctx.read_string(), // triggerTarget[i]
			    ctx.read_float()   // fireDelay[i]
			});
		}

		if (obj.saved) {
			// TODO: in save-games trigger lists behave differently
			(void) ctx.read_byte(); // actTarget
			(void) ctx.read_bool(); // sendOnTrigger
		}
	}

	void trigger_script::parse(trigger_script& obj, archive_reader& ctx, game_version version) {
		trigger::parse(obj, ctx, version);
		obj.function = ctx.read_string(); // scriptFunc
	}

	void trigger_change_level::parse(trigger_change_level& obj, archive_reader& ctx,
	                                 game_version version) { //
		trigger::parse(obj, ctx, version);
		obj.level_name = ctx.read_string(); // levelName
		obj.start_vob = ctx.read_string();  // startVobName
	}

	void trigger_world_start::parse(trigger_world_start& obj, archive_reader& ctx,
	                                game_version version) { //
		vob::parse(obj, ctx, version);
		obj.target = ctx.read_string();  // triggerTarget
		obj.fire_once = ctx.read_bool(); // fireOnlyFirstTime

		if (obj.saved && version == game_version::gothic_2) {
			// TODO: in G2 save-games movers behave differently
			(void) ctx.read_bool(); // hasFired
		}
	}

	void trigger_untouch::parse(trigger_untouch& obj, archive_reader& ctx, game_version version) {
		vob::parse(obj, ctx, version);
		obj.target = ctx.read_string(); // triggerTarget
	}
} // namespace phoenix::vobs