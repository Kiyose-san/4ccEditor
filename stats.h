#pragma once
//this file is meant to make updating the editor for stat changes exceedingly simple.
//stats use pes21 names
//stats that are listed as 0 will be replaced with the base_stat value in the editor.
//note that currently the AATF currently relies on all 4 of these types of players having different heights, but this could be changed if needed

namespace globalStats { //Global stats that apply to all players rather than any individual type
	const int heightColossal = 210;
	const int heightGiant = 190;
	const int heightTall = 185;
	const int heightMid = 180;
	const int heightManlet = 175;
	const int gk_height_override = 189; //Set to 0 if they use the same height system as regular players

	const int allowedBronze = 2;
	const int allowedSilver = 2;
	const int allowedGold = 1;

	const int allowedColossal = 0;
	const int colossal_foot_usage = 0; //Set to 0 if they are the same as regular players
	const int colossal_foot_acc = 0; //Set to 0 if they are the same as regular players
	const int colossal_card_mod = 0; //Set to 0 if they are the same as regular players
	const int colossal_apos_mod = 0; //Set to 0 if they are the same as regular players

	const int allowedGiant = 0;
	const int giant_foot_usage = 0; //Set to 0 if they are the same as regular players
	const int giant_foot_acc = 0; //Set to 0 if they are the same as regular players
	const int giant_card_mod = 0; //Set to 0 if they are the same as regular players
	const int giant_apos_mod = 0; //Set to 0 if they are the same as regular players

	const int allowedTall = 10;
	const int tall_foot_usage = 0; //Set to 0 if they are the same as regular players
	const int tall_foot_acc = 0; //Set to 0 if they are the same as regular players
	const int tall_card_mod = 0; //Set to 0 if they are the same as regular players
	const int tall_apos_mod = 0; //Set to 0 if they are the same as regular players

	const int allowedMid = 7;
	const int mid_foot_usage = 0; //Set to 0 if they are the same as regular players
	const int mid_foot_acc = 0; //Set to 0 if they are the same as regular players
	const int mid_card_mod = 0; //Set to 0 if they are the same as regular players
	const int mid_apos_mod = 0; //Set to 0 if they are the same as regular players

	const int allowedManlet = 6;
	const int manlet_foot_usage = 4; //Set to 0 if they are the same as regular players
	const int manlet_foot_acc = 4; //Set to 0 if they are the same as regular players
	const int manlet_card_mod = 1; //Set to 0 if they are the same as regular players
	const int manlet_apos_mod = 1; //Set to 0 if they are the same as regular players
}

namespace gold { //gold stats
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int skills = 6; //max number of non free skills allowed
	const int tricks = 12; //max number of trick cards allowed
	const int coms = 1; //free coms allowed
	const int a_pos = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 99; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
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
namespace silver { //silver stats
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int skills = 5; //max number of non free skills allowed
	const int tricks = 12; //max number of trick cards allowed
	const int coms = 1; //free coms allowed
	const int a_pos = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 94; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
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
namespace bronze { //bronze stats
	const int form = 8;
	const int injury_resistance = 2;
	const int weak_foot_usage = 4;
	const int weak_foot_accuracy = 4;
	const int skills = 5; //max number of non free skills allowed
	const int tricks = 12; //max number of trick cards allowed
	const int coms = 1; //free coms allowed
	const int a_pos = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 89; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
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

namespace regular { //nm 180 stats
	const int form = 4;
	const int injury_resistance = 1;
	const int weak_foot_usage = 2;
	const int weak_foot_accuracy = 2;
	const int skills = 4; //max number of non free skills allowed
	const int tricks = 12; //max number of trick cards allowed
	const int coms = 0; //free coms allowed
	const int a_pos = 2; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 77; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
	const int gk_base_stat = 77; //GK base stat value used if no changes. if a stat below is set at 0, this value will be used.
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

namespace goalkeeper {
	const int form = 4;
	const int injury_resistance = 1;
	const int weak_foot_usage = 2;
	const int weak_foot_accuracy = 2;
	const int skills = 4; //max number of non free skills allowed
	const int tricks = 12; //max number of trick cards allowed
	const int coms = 0; //free coms allowed
	const int a_pos = 1; //free a positions allowed, note this includes the A position that a registered position gives

	const int base_stat = 77; //base stat value used if no changes. if a stat below is set at 0, this value will be used.
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