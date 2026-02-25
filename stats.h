// Players with Registered Position of GK 72 OVR
// REMOVE: Nonmedals in the buffed player section may have the Weighted Pass and One-Touch Pass cards for free
// REMOVE: Players in the buffed player bracket with a Playable Position of LB, RB, CMF, or DMF have 2/2 Footedness. All other players have 4/4 Footedness.
// DOUBLE CHECK: GK height must be 185, not 183
// ADD: Captain gains free card on top of captaincy
// REMOVE: Players may have the First-Time Shot and Acrobatic Finishing skill cards for free
// REMOVE: Players may have the Long Ranger and Incisive Run COM Styles for free

#pragma once
//this file is meant to make updating the editor for stat changes exceedingly simple.
//stats use pes21 names
//stats that are listed as 0 will be replaced with the base_stat value in the editor.
//note that currently the AATF currently relies on all 4 of these types of players having different heights, but this could be changed if needed
namespace gold { //gold stats
	const int count = 1; //number of this type of player allowed
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int height = 195;
	const int skills = 8; //max number of non free skills allowed
	const int free_coms = 2; //free coms allowed
	const int free_a = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 99; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 0;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 0;
	const int place_kicking = 94;
	const int curl = 0;
	const int header = 0;
	const int defensive_awareness = 60;
	const int ball_winning = 94;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 0;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 0;
	const int stamina = 0;
	const int gk_awareness = 0;
	const int catching = 0;
	const int clearing = 0;
	const int reflexes = 0;
	const int gk_reach = 0;
	const int tight_possession = 0;
	const int aggression = 0;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };

}
namespace silver { //silver stats
	const int count = 2; //number of this type of player allowed
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int height = 195;
	const int skills = 8; //max number of non free skills allowed
	const int free_coms = 2; //free coms allowed
	const int free_a = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 94; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 99;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 99;
	const int place_kicking = 89;
	const int curl = 0;
	const int header = 99;
	const int defensive_awareness = 60;
	const int ball_winning = 89;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 0;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 0;
	const int stamina = 0;
	const int gk_awareness = 0;
	const int catching = 0;
	const int clearing = 0;
	const int reflexes = 0;
	const int gk_reach = 0;
	const int tight_possession = 0;
	const int aggression = 0;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };
}
namespace bronze { //bronze stats
	const int count = 2; //number of this type of player allowed
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int height = 190;
	const int skills = 8; //max number of non free skills allowed
	const int free_coms = 2; //free coms allowed
	const int free_a = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 89; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 94;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 94;
	const int place_kicking = 84;
	const int curl = 0;
	const int header = 94;
	const int defensive_awareness = 60;
	const int ball_winning = 84;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 0;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 0;
	const int stamina = 0;
	const int gk_awareness = 0;
	const int catching = 0;
	const int clearing = 0;
	const int reflexes = 0;
	const int gk_reach = 0;
	const int tight_possession = 0;
	const int aggression = 0;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };
}

namespace buffed { //buffed player stats
	const int count = 8; //number of this type of player allowed
	const int form = 4;
	const int injury_resistance = 1;
	const int weak_foot_usage = 4;
	const int weak_foot_usage_debuff = 2; //Under certain circumstances, weak foot must be this
	const int weak_foot_accuracy = 4;
	const int height = 185;
	const int skills = 7; //max number of non free skills allowed
	const int free_coms = 1; //free coms allowed
	const int free_a = 2; //free a positions allowed, note this includes the A position that a registered position gives


	const int base_stat = 85; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 90;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 0;
	const int place_kicking = 0;
	const int curl = 0;
	const int header = 0;
	const int defensive_awareness = 60;
	const int ball_winning = 60;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 0;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 75;
	const int stamina = 70;
	const int gk_awareness = 0;
	const int catching = 0;
	const int clearing = 0;
	const int reflexes = 0;
	const int gk_reach = 0;
	const int tight_possession = 0;
	const int aggression = 90;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };
}

namespace regular { //nm (nonbuffed) stats
	const int count = 10; //number of this type of player allowed
	const int form = 4;
	const int gk_form = 8;
	const int injury_resistance = 1;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int height = 180;
	const int gk_height = 185;
	const int skills = 7; //max number of non free skills allowed
	const int free_coms = 1; //free coms allowed
	const int free_a = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 80; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int gk_base_stat = 72; //GK base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 0;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 0;
	const int place_kicking = 0;
	const int curl = 0;
	const int header = 0;
	const int defensive_awareness = 70;
	const int ball_winning = 70;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 70;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 70;
	const int stamina = 65;
	const int gk_awareness = 72;
	const int catching = 72;
	const int clearing = 72;
	const int reflexes = 72;
	const int gk_reach = 72;
	const int tight_possession = 0;
	const int aggression = 90;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };
}
/*
namespace blank_example { //has all stats 0'd out for easier removal of stat changes
	const int count = 0; //number of this type of player allowed
	const int form = 0;
	const int injury_resistance = 0;
	const int weak_foot_usage = 0;
	const int weak_foot_accuracy = 0;
	const int height = 0;
	const int skills = 0; //max number of non free skills allowed
	const int free_coms = 0; //free coms allowed
	const int free_a = 0; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 0; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int offensive_awareness = 0;
	const int ball_control = 0;
	const int dribbling = 0;
	const int low_pass = 0;
	const int lofted_pass = 0;
	const int finishing = 0;
	const int place_kicking = 0;
	const int curl = 0;
	const int header = 0;
	const int defensive_awareness = 0;
	const int ball_winning = 0;
	const int kicking_power = 0;
	const int speed = 0;
	const int acceleration = 0;
	const int balance = 0;
	const int physical_contact = 0;
	const int jump = 0;
	const int stamina = 0;
	const int gk_awareness = 0;
	const int catching = 0;
	const int clearing = 0;
	const int reflexes = 0;
	const int gk_reach = 0;
	const int tight_possession = 0;
	const int aggression = 0;
	const int stat_array[] = { offensive_awareness, ball_control, dribbling, low_pass, lofted_pass, finishing, place_kicking, curl, header, defensive_awareness,
		ball_winning, kicking_power, speed, acceleration, balance, physical_contact, jump, stamina, gk_awareness, catching, clearing, reflexes, gk_reach,
		tight_possession, aggression };
}
*/