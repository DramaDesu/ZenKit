// Copyright © 2022 Luis Michaelis <lmichaelis.all+dev@gmail.com>
// SPDX-License-Identifier: MIT
#include <doctest/doctest.h>
#include <phoenix/phoenix.hh>
#include <phoenix/world.hh>

TEST_SUITE("world") {
	TEST_CASE("world meshes are read correctly") {
		auto in = phoenix::buffer::mmap("./samples/world.proprietary.zen");
		auto wld = phoenix::world::parse(in);

		auto& mesh = wld.world_mesh;
		CHECK(mesh.vertices.size() == 55439);
		CHECK(mesh.features.size() == 419936);
		CHECK(mesh.materials.size() == 2263);
		CHECK(mesh.name == "");

		auto box0 = mesh.bbox;
		CHECK(box0.min == glm::vec3 {0, 0, 0});
		CHECK(box0.max == glm::vec3 {0, 0, 0});

		auto obb = mesh.obb;
		CHECK(obb.center == glm::vec3 {0, 0, 0});
		CHECK(obb.axes[0] == glm::vec3 {0, 0, 0});
		CHECK(obb.axes[1] == glm::vec3 {0, 0, 0});
		CHECK(obb.axes[2] == glm::vec3 {0, 0, 0});
		CHECK(obb.half_width == glm::vec3 {0, 0, 0});

		auto& verts = mesh.vertices;
		CHECK(verts[0] == glm::vec3 {91365, -4026.60083, 46900});
		CHECK(verts[1] == glm::vec3 {92900, -4029.99976, 38399.9961});
		CHECK(verts[500] == glm::vec3 {44263.8203, 708.517822, 6841.18262});
		CHECK(verts[501] == glm::vec3 {45672.6094, 640.436157, 6877.81543});

		auto& feats = mesh.features;
		CHECK(feats[0].texture == glm::vec2 {1.11193848, 2.64415169});
		CHECK(feats[0].light == 4292927712);
		CHECK(feats[0].normal == glm::vec3 {0.0000220107158, 1, -0.000121058853});

		CHECK(feats[1].texture == glm::vec2 {-0.371101379, -0.909111022});
		CHECK(feats[1].light == 4292927712);
		CHECK(feats[1].normal == glm::vec3 {0.0000251403726, 1, -0.000138271935});

		CHECK(feats[500].texture == glm::vec2 {-0.524971008, 2.59478664});
		CHECK(feats[500].light == 4281084972);
		CHECK(feats[500].normal == glm::vec3 {-0.000046945388, -0.99999994, 0.000258200336});

		CHECK(feats[501].texture == glm::vec2 {1.93376923, -0.734043121});
		CHECK(feats[501].light == 4281084972);
		CHECK(feats[501].normal == glm::vec3 {0.000102534526, -1, -0.00014051389});

		auto& mats = mesh.materials;
		auto& mat0 = mats[0];
		auto& mat500 = mats[500];

		CHECK(mat0.name == "OWODWATSTOP");
		CHECK(mat0.group == phoenix::material_group::water);
		CHECK(mat0.texture == "OWODSEA_A0.TGA");

		CHECK(mat500.name == "OMWABROWNGREEN01");
		CHECK(mat500.group == phoenix::material_group::stone);
		CHECK(mat500.texture == "OMWABROWNGREEN01.TGA");

		auto polys = wld.world_mesh.polygons;
		CHECK(polys.material_indices.size() == 106722);
		CHECK(polys.lightmap_indices.size() == 106722);
		CHECK(polys.feature_indices.size() == 106722 * 3);
		CHECK(polys.vertex_indices.size() == 106722 * 3);
		CHECK(polys.flags.size() == 106722);

		CHECK(polys.material_indices[0] == 0);
		CHECK(polys.material_indices[26680] == 20);
		CHECK(polys.material_indices[53360] == 1097);
		CHECK(polys.material_indices[106721] == 4);

		CHECK(polys.lightmap_indices[0] == -1);
		CHECK(polys.lightmap_indices[26680] == -1);
		CHECK(polys.lightmap_indices[53360] == 557);
		CHECK(polys.lightmap_indices[106721] == -1);

		CHECK(polys.feature_indices[0 * 3 + 0] == 0);
		CHECK(polys.feature_indices[0 * 3 + 1] == 1);
		CHECK(polys.feature_indices[0 * 3 + 2] == 2);
		CHECK(polys.feature_indices[26680 * 3 + 0] == 100792);
		CHECK(polys.feature_indices[26680 * 3 + 1] == 100793);
		CHECK(polys.feature_indices[26680 * 3 + 2] == 100794);
		CHECK(polys.feature_indices[53360 * 3 + 0] == 210349);
		CHECK(polys.feature_indices[53360 * 3 + 1] == 210350);
		CHECK(polys.feature_indices[53360 * 3 + 2] == 210351);
		CHECK(polys.feature_indices[106721 * 3 + 0] == 419933);
		CHECK(polys.feature_indices[106721 * 3 + 1] == 419934);
		CHECK(polys.feature_indices[106721 * 3 + 2] == 419935);

		CHECK(polys.vertex_indices[0 * 3 + 0] == 0);
		CHECK(polys.vertex_indices[0 * 3 + 1] == 2);
		CHECK(polys.vertex_indices[0 * 3 + 2] == 1);
		CHECK(polys.vertex_indices[26680 * 3 + 0] == 14241);
		CHECK(polys.vertex_indices[26680 * 3 + 1] == 14243);
		CHECK(polys.vertex_indices[26680 * 3 + 2] == 14242);
		CHECK(polys.vertex_indices[53360 * 3 + 0] == 28518);
		CHECK(polys.vertex_indices[53360 * 3 + 1] == 28512);
		CHECK(polys.vertex_indices[53360 * 3 + 2] == 28520);
		CHECK(polys.vertex_indices[106721 * 3 + 0] == 55429);
		CHECK(polys.vertex_indices[106721 * 3 + 1] == 55428);
		CHECK(polys.vertex_indices[106721 * 3 + 2] == 54576);

		CHECK(polys.flags[0] == phoenix::polygon_flags {0, 0, 0, 0, 0, 0, 0, -1, 1, 1});
		CHECK(polys.flags[26680] == phoenix::polygon_flags {0, 0, 0, 0, 0, 0, 0, -1, 1, 1});
		CHECK(polys.flags[53360] == phoenix::polygon_flags {0, 1, 1, 0, 0, 0, 0, -1, 0, 0});
		CHECK(polys.flags[106721] == phoenix::polygon_flags {0, 0, 0, 0, 0, 0, 0, -1, 1, 1});
	}

	TEST_CASE("the bsp-tree is read correctly") {
		auto in = phoenix::buffer::mmap("./samples/world.proprietary.zen");
		auto wld = phoenix::world::parse(in);
		auto& tree = wld.world_bsp_tree;

		CHECK(tree.mode == phoenix::bsp_tree_mode::outdoor);

		auto& polys = tree.polygon_indices;
		CHECK(polys.size() == 480135);
		CHECK(polys[0] == 0);
		CHECK(polys[1] == 1);
		CHECK(polys[2] == 2);
		CHECK(polys[150] == 102);
		CHECK(polys[151] == 103);
		CHECK(polys[152] == 92);

		auto& nodes = tree.nodes;
		CHECK(nodes.size() == 6644);
		CHECK(nodes[0].plane == glm::vec4 {1, 0, 0, 18540.0156f});
		CHECK(nodes[0].front_index == 1);
		CHECK(nodes[0].parent_index == -1);
		CHECK(nodes[0].back_index == 1599);
		CHECK(nodes[0].polygon_index == 0);
		CHECK(nodes[0].polygon_count == 0);
		CHECK(nodes[0].bbox.min == glm::vec3 {-71919.9609f, -12000, -59900});
		CHECK(nodes[0].bbox.max == glm::vec3 {108999.992f, 20014.0371f, 67399.9921f});
		CHECK(!nodes[0].is_leaf());

		CHECK(nodes[1].plane == glm::vec4 {0, 0, 1, 3749.99609f});
		CHECK(nodes[1].front_index == 2);
		CHECK(nodes[1].parent_index == 0);
		CHECK(nodes[1].back_index == 445);
		CHECK(nodes[1].polygon_index == 0);
		CHECK(nodes[1].polygon_count == 0);
		CHECK(nodes[1].bbox.min == glm::vec3 {15499.999f, -12000, -59900});
		CHECK(nodes[1].bbox.max == glm::vec3 {108999.992f, 19502.1973f, 67399.9921f});
		CHECK(!nodes[1].is_leaf());

		auto& leaves = tree.leaf_node_indices;
		CHECK(leaves.size() == 3318);
		CHECK(leaves[0] == 5);
		CHECK(leaves[10] == 26);

		CHECK(nodes[5].is_leaf());
		CHECK(nodes[5].parent_index == 4);
		CHECK(nodes[5].polygon_index == 0);
		CHECK(nodes[5].polygon_count == 22);
		CHECK(nodes[5].bbox.min == glm::vec3 {81900, -4029.99976f, 28500.0039f});
		CHECK(nodes[5].bbox.max == glm::vec3 {100000, -4026.60083f, 53899.9922f});

		CHECK(nodes[26].is_leaf());
		CHECK(nodes[26].parent_index == 25);
		CHECK(nodes[26].polygon_index == 446);
		CHECK(nodes[26].polygon_count == 24);
		CHECK(nodes[26].bbox.min == glm::vec3 {48899.9961f, -4029.99976f, 47400});
		CHECK(nodes[26].bbox.max == glm::vec3 {67900, -4026.59961f, 67399.9921f});

		auto& sectors = tree.sectors;
		CHECK(sectors.size() == 299);

		CHECK(sectors[0].name == "WALD11");
		CHECK(sectors[0].node_indices.size() == 9);
		CHECK(sectors[0].portal_polygon_indices.size() == 24);

		CHECK(sectors[50].name == "OWCAVE01");
		CHECK(sectors[50].node_indices.size() == 4);
		CHECK(sectors[50].portal_polygon_indices.size() == 2);

		auto& portal_polys = tree.portal_polygon_indices;
		CHECK(portal_polys.size() == 0);

		CHECK(tree.light_points.size() == 3318);
		CHECK(tree.light_points[0] == glm::vec3 {-99, -99, -99});
	}

	TEST_CASE("the vob-tree is read correctly") {
		auto in = phoenix::buffer::mmap("./samples/world.proprietary.zen");
		auto wld = phoenix::world::parse(in);
		auto& vobs = wld.world_vobs;

		CHECK(vobs.size() == 14);

		// FIXME: Test all kinds of VOBs
		auto& vob0 = vobs[0];
		auto& vob13 = vobs[13];

		{
			auto box0 = vob0->bbox;
			CHECK(box0.min == glm::vec3 {-71919.9609, -13091.8232, -59900});
			CHECK(box0.max == glm::vec3 {108999.992, 20014.0352, 67399.9921});

			auto mat = vob0->rotation;
			CHECK(mat[0][0] == 1.0f);
			CHECK(mat[1][0] == 0.0f);
			CHECK(mat[2][0] == 0.0f);
			CHECK(mat[0][1] == 0.0f);
			CHECK(mat[1][1] == 1.0f);
			CHECK(mat[2][1] == 0.0f);
			CHECK(mat[0][2] == 0.0f);
			CHECK(mat[1][2] == 0.0f);
			CHECK(mat[2][2] == 1.0f);

			CHECK(vob0->vob_name == "LEVEL-VOB");
			CHECK(vob0->visual_name == "SURFACE.3DS");
			CHECK(vob0->preset_name.empty());
			CHECK(vob0->position == glm::vec3 {0, 0, 0});
			CHECK(!vob0->show_visual);
			CHECK(vob0->sprite_camera_facing_mode == phoenix::sprite_alignment::none);
			CHECK(vob0->anim_mode == phoenix::animation_mode::none);
			CHECK(vob0->anim_strength == 0.0f);
			CHECK(vob0->far_clip_scale == 0.0f);
			CHECK(vob0->cd_static);
			CHECK(!vob0->cd_dynamic);
			CHECK(!vob0->vob_static);
			CHECK(vob0->dynamic_shadows == phoenix::shadow_mode::none);
			CHECK(vob0->bias == 0);
			CHECK(!vob0->ambient);
			CHECK(!vob0->physics_enabled);

			auto& children = vob0->children;
			CHECK(children.size() == 7496);

			auto& child1 = children[0];

			{
				auto box1 = child1->bbox;
				CHECK(box1.min == glm::vec3 {-18596.9004, -161.17189, 4091.1333});
				CHECK(box1.max == glm::vec3 {-18492.0723, -111.171906, 4191.26221});

				auto matc = child1->rotation;
				CHECK(matc[0][0] == -0.779196978f);
				CHECK(matc[1][0] == 0.0f);
				CHECK(matc[2][0] == 0.626779079f);

				CHECK(matc[0][1] == 0.0f);
				CHECK(matc[1][1] == 1.0f);
				CHECK(matc[2][1] == 0.0f);

				CHECK(matc[0][2] == -0.626779079f);
				CHECK(matc[1][2] == 0.0f);
				CHECK(matc[2][2] == -0.779196978f);

				CHECK(child1->vob_name == "FP_CAMPFIRE_PATH_BANDITOS2_03_02");
				CHECK(child1->visual_name.empty());
				CHECK(child1->preset_name.empty());
				CHECK(child1->position == glm::vec3 {-18544.4863, -136.171906, 4141.19727});
				CHECK(!child1->show_visual);
				CHECK(child1->sprite_camera_facing_mode == phoenix::sprite_alignment::none);
				CHECK(child1->anim_mode == phoenix::animation_mode::none);
				CHECK(child1->anim_strength == 0.0f);
				CHECK(child1->far_clip_scale == 0.0f);
				CHECK(!child1->cd_static);
				CHECK(!child1->cd_dynamic);
				CHECK(!child1->vob_static);
				CHECK(child1->dynamic_shadows == phoenix::shadow_mode::none);
				CHECK(child1->bias == 0);
				CHECK(!child1->ambient);
				CHECK(!child1->physics_enabled);

				CHECK(child1->children.empty());
			}
		}

		{
			auto box2 = vob13->bbox;
			CHECK(box2.min == glm::vec3 {-9999.40234, -10000.0039, -9200});
			CHECK(box2.max == glm::vec3 {9060.59765, 5909.90039, 7537.47461});

			auto mat = vob13->rotation;
			CHECK(mat[0][0] == 1.0f);
			CHECK(mat[1][0] == 0.0f);
			CHECK(mat[2][0] == 0.0f);
			CHECK(mat[0][1] == 0.0f);
			CHECK(mat[1][1] == 1.0f);
			CHECK(mat[2][1] == 0.0f);
			CHECK(mat[0][2] == 0.0f);
			CHECK(mat[1][2] == 0.0f);
			CHECK(mat[2][2] == 1.0f);

			CHECK(vob13->vob_name == "LEVEL-VOB");
			CHECK(vob13->visual_name == "OLDCAMP.3DS");
			CHECK(vob13->preset_name.empty());
			CHECK(vob13->position == glm::vec3 {0, 0, 0});
			CHECK(!vob13->show_visual);
			CHECK(vob13->sprite_camera_facing_mode == phoenix::sprite_alignment::none);
			CHECK(vob13->anim_mode == phoenix::animation_mode::none);
			CHECK(vob13->anim_strength == 0.0f);
			CHECK(vob13->far_clip_scale == 0.0f);
			CHECK(!vob13->cd_static);
			CHECK(!vob13->cd_dynamic);
			CHECK(!vob13->vob_static);
			CHECK(vob13->dynamic_shadows == phoenix::shadow_mode::none);
			CHECK(vob13->bias == 0);
			CHECK(!vob13->ambient);
			CHECK(!vob13->physics_enabled);

			auto& children = vob13->children;
			CHECK(children.size() == 3250);
		}
	}

	TEST_CASE("the way-net is read correctly") {
		auto in = phoenix::buffer::mmap("./samples/world.proprietary.zen");
		auto wld = phoenix::world::parse(in);
		auto& waynet = wld.world_way_net;

		CHECK(waynet.waypoints.size() == 2784);
		CHECK(waynet.edges.size() == 3500);

		auto& wp0 = waynet.waypoints[0];
		auto& wp100 = waynet.waypoints[100];
		auto* wp500 = waynet.waypoint("OW_FOGDUNGEON_32");
		auto* wp_missing = waynet.waypoint("nonexistent");

		CHECK(wp0.name == "LOCATION_28_07");
		CHECK(wp0.water_depth == 0);
		CHECK(!wp0.under_water);
		CHECK(wp0.position == glm::vec3 {23871.457, -553.283813, 27821.3516});
		CHECK(wp0.direction == glm::vec3 {0.86651814, 0, -0.499145567});
		CHECK(wp0.free_point);

		CHECK(wp100.name == "CASTLE_MOVEMENT_STRAIGHT3");
		CHECK(wp100.water_depth == 0);
		CHECK(!wp100.under_water);
		CHECK(wp100.position == glm::vec3 {3362.21948, 8275.1709, -21067.9473});
		CHECK(wp100.direction == glm::vec3 {-0.342115372, 0, 0.939657927});
		CHECK(!wp100.free_point);

		CHECK(wp500 != nullptr);
		CHECK(wp500->name == "OW_FOGDUNGEON_32");
		CHECK(wp500->water_depth == 0);
		CHECK(!wp500->under_water);
		CHECK(wp500->position == glm::vec3 {26636.0645, -1802.15601, 10523.1445});
		CHECK(wp500->direction == glm::vec3 {-0.999390841, 0, 0.0348994918});
		CHECK(!wp500->free_point);

		CHECK(wp_missing == nullptr);

		auto& edge0 = waynet.edges[0];
		auto& edge5 = waynet.edges[5];
		auto& edge100 = waynet.edges[100];
		auto& edge500 = waynet.edges[500];

		CHECK(edge0.a == 20);
		CHECK(edge0.b == 21);

		// edge 6 is a reference
		CHECK(edge5.a == 28);
		CHECK(edge5.b == 30);

		CHECK(edge100.a == 123);
		CHECK(edge100.b == 126);

		CHECK(edge500.a == 521);
		CHECK(edge500.b == 515);
	}
}
