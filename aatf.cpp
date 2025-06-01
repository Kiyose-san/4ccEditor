#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#include "aatf.h"
#include <list>    
#ifndef UNICODE  
typedef std::string tstring;
typedef std::stringstream tstringstream;
#else
typedef std::wstring tstring;
typedef std::wstringstream tstringstream;
#endif

//Struct to hold the necessary data to check if each player skill matches its target rating and, if not, print an error message
struct skillCheck
{
	unsigned char c_skillRate; //The player's rating in a skill
	tstring s_skillName; //The skill name
	int n_minPesVersion; //The PES version in which skill was introduced (0 if in all versions)
	int n_targetRate; //What the player's rating in this skill should be under the rules
};

//This array encodes the mapping between the registered position IDs (0-12) used in the player_export struct's reg_pos field
// and the corresponding index in the playable position array (player_export play_pos).  It is used to check that a player has 
// playable position set to A in the same position in which they are registered.
/* position	reg_pos	play_pos
	GK		0		12
	CB		1		9
	LB		2		10
	RB		3		11
	DMF		4		5
	CMF		5		6
	LMF		6		7
	RMF		7		8
	AMF		8		4
	LWF		9		2
	RWF		10		3
	SS		11		1
	CF		12		0 */
int regPosToPlayPosMap[13] = { 12, 9, 10, 11, 5, 6, 7, 8, 4, 2, 3, 1, 0 };

//============================
//AATF Settings
int manletBonus = 5;
int silverManletBonus = 0;
int goldManletBonus = 0;
int silverGiantPen = 4;
int goldGiantPen = 0;

int goldRate = 99; //Player skill ratings
int silverRate = 92;
int regRate = 77;
int gkRate = 77;

int reqNumGold = 2; //Numbers of medals
int reqNumSilver = 2;

int goldForm = 8; //possible range 1-8
int silverForm = 8;
int regForm = 4;

int goldIR = 3; //Injury resistence (possible range 1-3)
int silverIR = 3;
int regIR = 1;

int goldWeakFootUse = 4; //Gold medal weak foot usage limit
int silverWeakFootUse = 4;
int regWeakFootUse = 2;

int goldWeakFootAcc = 2; //Gold medal weak foot accuracy limit
int silverWeakFootAcc = 2;
int regWeakFootAcc = 2;

int manletCardBonus = 1; //Manlets get 1 extra card
int manletWeakFootUse = 4; //Manlets get 4/4 weak foot usage/accuracy
int manletWeakFootAcc = 4;
int manletPosBonus = 1; //Manlets get 1 extra double A position

int gkSkillCards = 2; //Skill cards
int regSkillCards = 3;
int silverSkillCards = 4;
int goldSkillCards = 5;

int gkTrickCards = 0; //Trick cards
int regTrickCards = 2;
int silverTrickCards = 3;
int goldTrickCards = 3;

int regCOM = 0; //COM playing styles
int silverCOM = 1;
int goldCOM = 2;

int greenGiga = 0; //Green height bracket
int greenGiant = 6;
int greenTall = 6;
int greenMid = 6;
int greenManlet = 5;

int redGiga = 0; //Red height bracket
int redGiant = 0;
int redTall = 10;
int redMid = 7;
int redManlet = 6;

int heightGiga = 199; //Player heights in each category
int heightGiant = 194;
int heightTall = 185;
int heightTallGK = 189;
int heightMid = 180;
int heightManlet = 175;

//VGL Settings
int manletBonus_vgl = 0;
int silverManletBonus_vgl = 0;
int goldGiantPen_vgl = 0;
int silverGiantPen_vgl = 0;
int goldRate_vgl = 99;
int silverRate_vgl = 88;
int regRate_vgl = 77;
int gkRate_vgl = 77;
int reqNumGold_vgl = 2;
int reqNumSilver_vgl = 3;

int goldForm_vgl = 8;
int silverForm_vgl = 8;
int regForm_vgl = 4;

int goldIR_vgl = 2; //Injury resistence
int silverIR_vgl = 2;
int regIR_vgl = 1;

int goldWeakFoot_vgl = 4;
int silverWeakFoot_vgl = 4;
int regWeakFoot_vgl = 2;

int gkSkillCards_vgl = 3;
int regSkillCards_vgl = 3;
int silverSkillCards_vgl = 4;
int goldSkillCards_vgl = 5;

int gkTrickCards_vgl = 99;
int regTrickCards_vgl = 99;
int silverTrickCards_vgl = 99;
int goldTrickCards_vgl = 99;

int gkCOM_vgl = 0;
int regCOM_vgl = 0;
int silverCOM_vgl = 1;
int goldCOM_vgl = 1;

int blueColossal_vgl = 0;
int blueGiant_vgl = 0;
int blueTall_vgl = 0;
int blueMid_vgl = 0;
int blueManlet_vgl = 0;

int purpleColossal_vgl = 0;
int purpleGiant_vgl = 0;
int purpleTall_vgl = 10;
int purpleMid_vgl = 7;
int purpleManlet_vgl = 6;

int heightColossal_vgl = 210;
int heightGiant_vgl = 194;
int heightTall_vgl = 185;
int heightTallGK_vgl = 189;
int heightMid_vgl = 180;
int heightManlet_vgl = 175;

int numGK_vgl = 0;
//Count of player ratings
int numReg_vgl = 0;
int numSilver_vgl = 0;
int numGold_vgl = 0;
//Count of height brackets
int numColossal_vgl = 0;
int numGiant_vgl = 0;
int numTall_vgl = 0;
int numMid_vgl = 0;
int numManlet_vgl = 0;


int goldA_vgl = 2;
int silverA_vgl = 2;
int regA_vgl = 2;
int manletA_vgl = 3;


void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players)
{
	player_entry player;
	tstring msgOut;
	msgOut += _T("Team: ");
	msgOut += gteams[teamSel].name;
	msgOut += _T("\r\n");

	//============================

	bool hasCaptain = false;
	int numGK = 0;
	//Count of player ratings
	int numReg = 0;
	int numSilver = 0;
	int numGold = 0;
	//Count of height brackets
	int numGiga = 0;
	int numGiant = 0;
	int numTall = 0;
	int numMid = 0;
	int numManlet = 0;
	bool usingRed = true;
	bool eCheck = false;

	//Run through all players once to determine height system
	for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for (int jj = 0; jj < gnum_players; jj++)
		{
			if (gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}
		//If any player is in the green height brackets, team is on Green height system and we can halt
		if (player.height >= heightGiant)
		{
			usingRed = false;
			break;
		}
	}

	//Now check each player for errors
	int errorTot = 0;
	for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
	{
		//Find each player on team
		for (int jj = 0; jj < gnum_players; jj++)
		{
			if (gplayers[jj].id == gteams[teamSel].players[ii])
			{
				player = gplayers[jj];
				break;
			}
		}

		msgOut += _T("\x2022 Checking ");
		msgOut += player.name;
		msgOut += _T("\r\n");

		tstringstream errorMsg;

		int cardCount = 0;
		int cardMod = 0;
		int cardLimit = 0;
		int heightMod = 0;
		int weakFootUse = 0;
		int weakFootAcc = 0;
		bool hasTrick = false;
		int targetRate = 0, targetRate2 = 0, targetRate3 = 0;
		int rating = player.drib;
		rating = max(player.gk, rating);
		rating = max(player.finish, rating);
		rating = max(player.lowpass, rating);
		rating = max(player.loftpass, rating);
		rating = max(player.header, rating);
		rating = max(player.swerve, rating);
		rating = max(player.catching, rating);
		rating = max(player.clearing, rating);
		rating = max(player.reflex, rating);
		rating = max(player.body_ctrl, rating);
		if (pesVersion > 16) rating = max(player.phys_cont, rating); //Not in 16
		rating = max(player.kick_pwr, rating);
		rating = max(player.exp_pwr, rating);
		rating = max(player.ball_ctrl, rating);
		rating = max(player.ball_win, rating);
		rating = max(player.jump, rating);
		rating = max(player.cover, rating);
		rating = max(player.place_kick, rating);
		rating = max(player.stamina, rating);
		rating = max(player.speed, rating);
		if (pesVersion > 19) rating = max(player.aggres, rating);

		/*if(player.injury+1 > 3)
		{
			errorTot++;
			errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", cannot exceed 3; ");
		}*/

		//Check if this player is the captain
		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind]) hasCaptain = true;

		//Check if registered pos has playable set to A
		int requiredAPos = regPosToPlayPosMap[player.reg_pos];
		if (player.play_pos[requiredAPos] != 2)
		{
			errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}

		//Count number of registered GKs
		if (player.reg_pos == 0) numGK++;

		//Count A positions
		int countA = 0;
		for (int jj = 0; jj < 13; jj++)
		{
			if (player.play_pos[jj] > 0)
				countA++;
		}

		//If more than 1 A, 1 card less for each
		if (countA > 1)
		{
			if (player.play_pos[12] == 2) //Can't have GK as second A
			{
				errorTot++;
				errorMsg << _T("Has GK as second A position; ");
			}
			cardMod -= (countA - 1);
		}

		//Count cards
		int numTrick = 0;
		int numCom = 0;
		int numSkill;
		if (pesVersion == 19) numSkill = 39;
		else if (pesVersion > 19) numSkill = 41;
		else numSkill = 28;
		for (int jj = 0; jj < numSkill; jj++)
		{
			if (player.play_skill[jj])
			{
				cardCount++;
				//SPECIAL Winter/Spring 24: Malicia (21) is a free card
				if (jj == 21) cardMod++;
				//Captain gets free captaincy card
				if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind])
					cardMod++;
				//Trick cards may be free, count number
				if (jj < 6 || jj == 16 || jj == 28 || jj == 29 || jj == 30 || jj == 34)
				{
					hasTrick = true;
					numTrick++;
				}
			}
		}
		for (int jj = 0; jj < 7; jj++)
		{
			if (player.com_style[jj])
			{
				cardCount++;
				numCom++;
			}
		}

		if (player.age < 15 || player.age>50)
		{
			errorTot++;
			errorMsg << _T("Age out of range (15,50); ");
		}

		if (player.weight<max(30, player.height - 129) || player.weight>(player.height - 81))
		{
			errorTot++;
			errorMsg << _T("Weight out of range (") << max(30, player.height - 129) << _T(",") << player.height - 81 << _T("); ");
		}

		/* REGULAR */
		if (rating < silverRate - silverGiantPen) //Regular player
		{
			numReg++;
			targetRate = regRate;
			targetRate2 = regRate;
			targetRate3 = regRate;
			if (player.reg_pos == 0) //GK target rate is 77
			{
				targetRate = gkRate;
				targetRate2 = gkRate;
				targetRate3 = gkRate;
			}

			weakFootUse = regWeakFootUse;
			weakFootAcc = regWeakFootAcc;

			/*if(countA > 3)
			{
				errorTot++;
				errorMsg << _T("Regular player with > 3 A positions; ");
			}*/

			/*//SPECIAL Summer 24: Malicia (21) is now mandatory on all non-medal players
			if (!player.play_skill[21])
			{
				errorTot++;
				errorMsg << _T("Malicia card is mandatory for all non-medal players; ");
			}*/

			if (player.form + 1 != regForm)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << regForm << _T("; ");
			}

			if (player.reg_pos == 0) //GK gets 2 cards
			{
				cardMod += min(gkTrickCards, numTrick); //1 free tricks
				cardLimit = gkSkillCards + cardMod;

				if (player.height > heightMid && player.height < heightTallGK)
				{
					errorTot++;
					errorMsg << _T("GKs in this bracket must be ") << heightTallGK << _T("cm; ");
				}
				//SPECIAL Autumn 24 - GK and medals can'ts be in giant height bracket
				if (player.height >= heightGiant)
				{
					errorMsg << _T("GK heights cannot be ") << heightGiant << _T("cm; ");
				}
			}
			else
			{
				cardMod += min(regCOM, numCom); //0 free COM styles
				cardMod += min(regTrickCards, numTrick); //2 free tricks
				//cardMod += min(1, (countA - 1)); //1 free A-position
				cardLimit = regSkillCards + cardMod; //3 skill cards
			}

			if (player.injury + 1 > regIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << regIR << _T("; ");
			}

			if (player.height <= heightManlet && usingRed)
			{
				targetRate += manletBonus;
				targetRate2 += manletBonus;
				targetRate3 += manletBonus;
			}

			/*//SPECIAL Spring 24: non-medals that are registered in a blue position (CB, LB, RB) get +5 defensive prowess
			if (player.reg_pos >= 1 && player.reg_pos <= 3)
			{
				targetRate2 += 5;
			}*/

			/*//SPECIAL Spring 24: red heights non-medals registered in a red position (CF/SS/LWF/RWF) receive a +5 boost to all stats and can stack with the boost from being 175cm however these players cannot be given a 2nd A position
			if (player.reg_pos >= 9 && player.reg_pos <= 12 && usingRed)
			{
				targetRate += 5;
				targetRate2 += 5;
				//SPECIAL Summer 24: Red Position non-medal manlet players (CF/SS/LWF/RWF) have stamina stat = 77
				if (player.height <= heightManlet && usingRed)
					targetRate3 = regRate;
				else
					targetRate3 += 5;
				if (countA > 1)
				{
					errorTot++;
					errorMsg << _T("Illegal 2nd A position on red heights non-medal forward; ");
				}
			}*/

			/*//SPECIAL Summer 24: green heights non-medals registered in a red position (CF/SS/LWF/RWF) get an additional 5cm of height except for 199cm players
			if (player.reg_pos >= 9 && player.reg_pos <= 12 && !usingRed && player.height <= heightGiant)
			{
				heightMod = 5;
			}*/

			if (eCheck)
			{
				if (player.reg_pos == 0)
				{
					if (numTrick < gkTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << gkTrickCards << _T("; ");
					if (numCom < regCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << regCOM << _T("; ");
				}
				else
				{
					if (numTrick < regTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << regTrickCards << _T("; ");
					if (numCom < regCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << regCOM << _T("; ");
				}
				if (player.injury + 1 < regIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << regIR << _T("; ");
			}
		}
		/* SILVER */
		else if (rating < goldRate - goldGiantPen) //Silver player
		{
			numSilver++;
			targetRate = silverRate;
			targetRate2 = silverRate;
			targetRate3 = silverRate;

			weakFootUse = silverWeakFootUse;
			weakFootAcc = silverWeakFootAcc;

			if (numSilver > reqNumSilver)
			{
				errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
			if (player.form + 1 != silverForm)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << silverForm << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if (player.height >= heightGiant) //HA get penalty
			{
				targetRate -= silverGiantPen;
				targetRate2 -= silverGiantPen;
				targetRate3 -= silverGiantPen;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += silverManletBonus;
				targetRate2 += silverManletBonus;
				targetRate3 += silverManletBonus;
			}
			cardMod += min(silverTrickCards, numTrick); //3 free tricks
			cardMod += min(silverCOM, numCom); //1 free COM
			//cardMod += min(1, (countA - 1)); //1 free A-position
			cardLimit = silverSkillCards + cardMod; //4 skill cards

			if (player.injury + 1 > silverIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << silverIR << _T("; ");
			}

			if (eCheck)
			{
				if (numTrick < silverTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << silverTrickCards << _T("; ");
				if (numCom < silverCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << silverCOM << _T("; ");
				if (player.injury + 1 < silverIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << silverIR << _T("; ");
			}
		}
		/* GOLD */
		else //rating == 99 //Gold player
		{
			numGold++;
			targetRate = goldRate;
			targetRate2 = goldRate;
			targetRate3 = goldRate;

			weakFootUse = goldWeakFootUse;
			weakFootAcc = goldWeakFootAcc;

			if (numGold > reqNumGold)
			{
				errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
			if (player.form + 1 != goldForm)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << goldForm << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}
			if (player.height >= heightGiant) //Medal HA penalty
			{
				targetRate -= goldGiantPen;
				targetRate2 -= goldGiantPen;
				targetRate3 -= goldGiantPen;
			}
			else if (player.height <= heightManlet && usingRed)
			{
				targetRate += goldManletBonus;
				targetRate2 += goldManletBonus;
				targetRate3 += goldManletBonus;
			}

			if (player.height > heightGiant)
			{
				errorMsg << _T("Gold heights cannot exceed ") << heightGiant << _T("cm; ");
			}

			cardMod += min(goldTrickCards, numTrick); //4 free tricks
			cardMod += min(goldCOM, numCom); //2 free COMs
			cardLimit = goldSkillCards + cardMod; //5 skill cards

			if (player.injury + 1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << goldIR << _T("; ");
			}

			if (eCheck)
			{
				if (cardCount < 10)
				{
					if (numTrick < goldTrickCards) errorMsg << _T("WARN: Has ") << numTrick << _T(" trick cards, allowed ") << goldTrickCards << _T("; ");
					if (numCom < goldCOM) errorMsg << _T("WARN: Has ") << numCom << _T(" COM cards, allowed ") << goldCOM << _T("; ");
				}
				if (player.injury + 1 < goldIR) errorMsg << _T("WARN: Has inj resist") << player.injury + 1 << _T(", allowed ") << goldIR << _T("; ");
			}

			//SPECIAL Spring 25 - GK and gold medals can't be in giant height bracket
			if (player.height >= heightGiant)
			{
				errorMsg << _T("Gold medal heights cannot be ") << heightGiant << _T("cm; ");
			}
		}

		//Check player height
		if (((player.height - heightMod) <= heightManlet))
		{
			numManlet++;
			cardLimit += manletCardBonus; //Manlets get a bonus card
			if (countA > 1) cardLimit += manletPosBonus; //Manlets get a bonus double A position
			weakFootUse = manletWeakFootUse; //Manlets get weak foot acc/use 4/4
			weakFootAcc = manletWeakFootAcc;
		}
		else if ((player.height - heightMod) <= heightMid)
		{
			numMid++;
		}
		else if ((player.height - heightMod) == heightTall)
			numTall++;
		else if ((player.height - heightMod) == heightTallGK && player.reg_pos == 0) //GK
			numTall++;
		else if ((player.height - heightMod) == heightGiant)
			numGiant++;
		else if ((player.height - heightMod) == heightGiga)
			numGiga++;
		else
		{
			errorTot++;
			errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
		}

		//Check weak foot ratings
		if (player.weak_use + 1 > weakFootUse)
		{
			errorTot++;
			errorMsg << _T("Weak foot usage > ") << weakFootUse << _T("; ");
		}
		if (player.weak_acc + 1 > weakFootAcc)
		{
			errorTot++;
			errorMsg << _T("Weak foot accuracy > ") << weakFootAcc << _T("; ");
		}

		//Check player card count
		if (cardCount > cardLimit)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
		}

		//Check PES skill card limit of 10
		if (cardCount - numCom > 10)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numCom << _T(" skill cards, PES limit is 10, please swap to COM cards or trade for additional A positions; ");
		}

		if (eCheck)
		{
			if (cardCount < min(cardLimit, 10)) errorMsg << _T("WARN: Has ") << cardCount << _T(" cards, allowed ") << cardLimit << _T("; ");
			if (player.weak_use + 1 < weakFootUse) errorMsg << _T("WARN: Has weak usage") << player.weak_use + 1 << _T(", allowed ") << weakFootUse << _T("; ");
			if (player.weak_acc + 1 < weakFootAcc) errorMsg << _T("WARN: Has weak accuracy") << player.weak_acc + 1 << _T(", allowed ") << weakFootAcc << _T("; ");
		}

		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings
		//								c_skillRate			s_skillName			n_minPesVersion	n_targetRate
		skillCheck skillChecks[25] = { {player.drib,		_T("Dribbling"),			0,		targetRate	},
										{player.gk,			_T("Goalkeeping"),			0,		targetRate	},
										{player.finish,		_T("Finishing"),			0,		targetRate	},
										{player.lowpass,	_T("Low Pass"),				0,		targetRate	},
										{player.loftpass,	_T("Lofted Pass"),			0,		targetRate	},
										{player.header,		_T("Header"),				0,		targetRate	},
										{player.swerve,		_T("Swerve"),				0,		targetRate	},
										{player.catching,	_T("Catching"),				0,		targetRate	},
										{player.clearing,	_T("Clearing"),				0,		targetRate	},
										{player.reflex,		_T("Reflexes"),				0,		targetRate	},
										{player.body_ctrl,	_T("Body Control"),			0,		targetRate	},
										{player.phys_cont,	_T("Physical Contact"),		17,		targetRate	},
										{player.kick_pwr,	_T("Kicking Power"),		0,		targetRate	},
										{player.exp_pwr,	_T("Explosive Power"),		0,		targetRate	},
										{player.ball_ctrl,	_T("Ball Control"),			0,		targetRate	},
										{player.ball_win,	_T("Ball Winning"),			0,		targetRate	},
										{player.jump,		_T("Jump"),					0,		targetRate	},
										{player.cover,		_T("Coverage"),				0,		targetRate	},
										{player.place_kick, _T("Place Kicking"),		0,		targetRate	},
										{player.stamina,	_T("Stamina"),				0,		targetRate3	},
										{player.speed,		_T("Speed"),				0,		targetRate	},
										{player.atk,		_T("Attacking Prowess"),	0,		targetRate	},
										{player.def,		_T("Defensive Prowess"),	0,		targetRate2	},
										{player.tight_pos,	_T("Tight Possession"),		20,		targetRate	},
										{player.aggres,		_T("Aggression"),			20,		targetRate	} };

		for (int ii = 0; ii < 25; ii++)
		{
			if (skillChecks[ii].n_minPesVersion <= pesVersion && skillChecks[ii].c_skillRate != skillChecks[ii].n_targetRate)
			{
				errorTot++;
				errorMsg << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be ") << skillChecks[ii].n_targetRate << _T("; ");
			}
		}

		if (errorMsg.rdbuf()->in_avail())
		{
			errorMsg << _T("\r\n");
			msgOut += _T("\t");
			msgOut += errorMsg.str();
		}
	}
	//Team level errors
	int diff;
	tstringstream errorMsg;

	if (!hasCaptain)
	{
		errorTot++;
		errorMsg << _T("Team must have an assigned Captain; ");
	}

	//Must have at least 1 GK
	if (numGK < 1)
	{
		errorTot++;
		errorMsg << _T("Team must have a registered GK; ");
	}

	//Check heights
	if (!usingRed) //Using Green height system
	{
		msgOut += _T("Using Green height system\r\n");
		if (diff = greenGiga - numGiga)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numGiga << _T("/") << greenGiga << _T(" ") << heightGiga << _T("cm players; ");
		}
		if (diff = greenGiant - numGiant)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numGiant << _T("/") << greenGiant << _T(" ") << heightGiant << _T("cm players; ");
		}
		if (diff = greenTall - numTall)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numTall << _T("/") << greenTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
		}
		if (diff = greenMid - numMid)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numMid << _T("/") << greenMid << _T(" ") << heightMid << _T("cm players; ");
		}
		if (diff = greenManlet - numManlet)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numManlet << _T("/") << greenManlet << _T(" ") << heightManlet << _T("cm players; ");
		}
	}
	else //Using Red height system
	{
		msgOut += _T("Using Red height system\r\n");
		if (diff = numGiga)
		{
			errorTot += diff;
			errorMsg << _T("Has ") << numGiga << _T("/") << redGiga << _T(" ") << heightGiga << _T("cm players; ");
		}
		if (diff = numGiant)
		{
			errorTot += diff;
			errorMsg << _T("Has ") << numGiant << _T("/") << redGiant << _T(" ") << heightGiant << _T("cm players; ");
		}
		if (diff = redTall - numTall)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numTall << _T("/") << redTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
		}
		if (diff = redMid - numMid)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numMid << _T("/") << redMid << _T(" ") << heightMid << _T("cm players; ");
		}
		if (diff = redManlet - numManlet)
		{
			if (diff > 0)
			{
				errorTot += diff;
			}
			else
			{
				errorTot -= diff;
			}
			errorMsg << _T("Has ") << numManlet << _T("/") << redManlet << _T(" ") << heightManlet << _T("cm players; ");
		}
	}
	if (errorMsg.rdbuf()->in_avail())
	{
		errorMsg << _T("\r\n");
		msgOut += errorMsg.str();
		errorMsg.clear();
		errorMsg.str(tstring());
	}

	//Check ability stats
	if (numReg != (23 - reqNumSilver - reqNumGold))
	{
		errorTot++;
		errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << 23 - reqNumSilver - reqNumGold << _T("; ");
	}
	if (numSilver != reqNumSilver)
	{
		errorTot++;
		errorMsg << _T("Number of Silver medals is ") << numSilver << _T(", should be ") << reqNumSilver << _T("; ");
	}
	if (numGold != reqNumGold)
	{
		errorTot++;
		errorMsg << _T("Number of Gold medals is ") << numGold << _T(", should be ") << reqNumGold << _T("; ");
	}
	if (errorMsg.rdbuf()->in_avail())
		errorMsg << _T("\r\n");
	errorMsg << _T("\r\nErrors: ") << errorTot << _T("\r\n");
	msgOut += errorMsg.str();

	SetWindowText(GetDlgItem(hAatfbox, IDT_AATFOUT), msgOut.c_str());
	if (errorTot)
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("KWABxport melty in the 'tor"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("Well, Seymour, this export made it... despite your directions"));
}

void aatf_single_vgl(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players, bool useSuggestions)
{
    player_entry player;
    std::list<player_entry> manlets_without_bonus;
    tstring msgOut;
    msgOut += _T("Team: ");
    msgOut += gteams[teamSel].name;
    msgOut += _T("\r\n");

    bool isManlet = false;
    bool usingPurple = true;

    numGK_vgl = 0;
    //Player ratings
    numReg_vgl = 0;
    numSilver_vgl = 0;
    numGold_vgl = 0;
    //Height brackets
    numColossal_vgl = 0;
    numGiant_vgl = 0;
    numTall_vgl = 0;
    numMid_vgl = 0;
    numManlet_vgl = 0;
    int numTrickOrCom = 0;

    int errorTot = 0;
    int suggestionTot = 0;

    bool captainHasCard = false;

    for (int ii = 0; ii < gteams[teamSel].num_on_team; ii++)
    {
        //Find each player on team
        for (int jj = 0; jj < gnum_players; jj++)
        {
            if (gplayers[jj].id == gteams[teamSel].players[ii])
            {
                player = gplayers[jj];
                break;
            }
        }

        msgOut += _T("\x2022 Checking ");
        msgOut += player.name;
        msgOut += _T("\r\n");

        tstringstream errorMsg;
        tstringstream suggestionMsg;

        int cardCount = 0;
        int cardMod = 0;
        int cardLimit = 0;
        bool hasTrick = false;
        int weakFoot = 0;
        int targetRate = 0, targetRate2 = 0;
        int rating = player.drib;
        rating = max(player.gk, rating);
        rating = max(player.finish, rating);
        rating = max(player.lowpass, rating);
        rating = max(player.loftpass, rating);
        rating = max(player.header, rating);
        rating = max(player.swerve, rating);
        rating = max(player.catching, rating);
        rating = max(player.clearing, rating);
        rating = max(player.reflex, rating);
        rating = max(player.body_ctrl, rating);
        if (pesVersion > 16) rating = max(player.phys_cont, rating); //Not in 16
        rating = max(player.kick_pwr, rating);
        rating = max(player.exp_pwr, rating);
        rating = max(player.ball_ctrl, rating);
        rating = max(player.ball_win, rating);
        rating = max(player.jump, rating);
        rating = max(player.cover, rating);
        rating = max(player.place_kick, rating);
        rating = max(player.stamina, rating);
        rating = max(player.speed, rating);
        if (pesVersion > 19) rating = max(player.aggres, rating);

        //Check if registered pos has playable set to A
        int requiredAPos = regPosToPlayPosMap[player.reg_pos];
        if (player.play_pos[requiredAPos] != 2)
        {
            errorTot++;
            errorMsg << _T("Doesn't have A in registered position; ");
        }

        //Count A positions
        for (int jj = 0; jj < 13; jj++)
        {
            if (player.play_pos[jj] == 1) {
                errorTot++;
                errorMsg << _T("Cannot have B as playable position; ");
            }
        }

        //Count A positions
        int countA = 0;
        for (int jj = 0; jj < 13; jj++)
        {
            if (player.play_pos[jj] > 0)
                countA++;
        }

        //If more than 1 A, 1 card less for each (Not for VGL)
        if (countA > 1)
        {
            if (player.play_pos[12] == 2) //Can't have GK as second A
            {
                errorTot++;
                errorMsg << _T("Has GK as second A position; ");
            }
            //cardMod -= (countA - 1);
        }

        //Count cards
        int numTrick = 0;
        int numCom = 0;
        int numSkill;
        if (pesVersion == 19) numSkill = 39;
        else if (pesVersion > 19) numSkill = 41;
        else numSkill = 28;
        for (int jj = 0; jj < numSkill; jj++)
        {
            if (player.play_skill[jj])
            {
                cardCount++;
                //Captain gets free captaincy card
                if (jj == 25 && player.id == gteams[teamSel].players[gteams[teamSel].captain_ind]) {
                    captainHasCard = true;
                    cardMod++;
                }

                //Trick cards may be free, count number
                //if(jj<6 || jj==16 || jj==28 || jj==29 || jj==30 || jj==34)
                if (jj < 6 || jj == 16 || jj == 21 || jj == 28 || jj == 29 || jj == 30 || jj == 34) //<- this is for PES19
                {
                    hasTrick = true;
                    numTrick++;
                }
            }
        }

        //Captain gets a free regular card
        if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind]) {
            cardMod++;
        }

        for (int jj = 0; jj < 7; jj++)
        {
            if (player.com_style[jj])
            {
                cardCount++;
                numCom++;
            }
        }

        isManlet = false;
        if (player.height <= 175)
        {
            isManlet = true;
            numManlet_vgl++;
            cardMod++; //Manlets get a bonus card
            if (player.height < 175 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Height can be increased to 175]; ");
            }
        }
        else if (player.height == heightMid_vgl)
            numMid_vgl++;
        else if (player.height == heightTall_vgl)
            numTall_vgl++;
        else if (player.height == heightTallGK_vgl && player.reg_pos == 0) //GK
            numTall_vgl++;
        else if (player.height == heightGiant_vgl)
            numGiant_vgl++;
        else if (player.height == heightColossal_vgl)
            numColossal_vgl++;
        else
        {
            errorTot++;
            errorMsg << _T("Illegal height (") << player.height << _T(" cm); ");
        }

        if (player.age < 15 || player.age>50)
        {
            errorTot++;
            errorMsg << _T("Age out of range (15,50); ");
        }

        if (player.weight<max(30, player.height - 129) || player.weight>(player.height - 81))
        {
            errorTot++;
            errorMsg << _T("Weight out of range (") << max(30, player.height - 129) << _T(",") << player.height - 81 << _T("); ");
        }

        /* REGULAR */
        if (rating < silverRate_vgl - silverGiantPen_vgl) //Regular player
        {
            numReg_vgl++;
            targetRate = regRate_vgl;
            targetRate2 = regRate_vgl;
            if (player.reg_pos == 0) //GK target rate is 77
            {
                targetRate = gkRate_vgl;
                targetRate2 = gkRate_vgl;
            }

            weakFoot = regWeakFoot_vgl;

            if (player.height > heightManlet_vgl)
            {
                if (player.weak_use + 1 > 2)
                {
                    errorTot++;
                    errorMsg << _T("Weak foot usage > 2; ");
                }
                if (player.weak_acc + 1 > 2)
                {
                    errorTot++;
                    errorMsg << _T("Weak foot accuracy > 2; ");
                }

                if (player.weak_use + 1 < 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Weak foot usage < 2]; ");
                }
                if (player.weak_acc + 1 < 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Weak foot accuracy < 2]; ");
                }
            }
            else {
                if (player.weak_use + 1 < 4 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Weak foot usage < 4]; ");
                }
                if (player.weak_acc + 1 < 4 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Weak foot accuracy < 4]; ");
                }
            }

            if (player.form + 1 != regForm_vgl)
            {
                errorTot++;
                errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << regForm_vgl << _T("; ");
            }

            if (isManlet) {
                if (countA > manletA_vgl) {
                    cardMod -= (countA - manletA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < manletA_vgl && player.play_pos[12] != 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << manletA_vgl << _T("]; ");
                }
            }
            else {
                if (countA > regA_vgl) {
                    cardMod -= (countA - regA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < regA_vgl && player.play_pos[12] != 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << regA_vgl << _T("]; ");
                }
            }

            if (player.reg_pos == 0) //GK gets 2 cards
            {
                cardMod += min(gkTrickCards_vgl, numTrick); //1 free tricks
                cardMod += min(gkCOM_vgl, numCom); //0 free COM styles
                cardLimit = gkSkillCards_vgl + cardMod;
                if (cardCount > cardLimit)
                {
                    errorTot++;
                    errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
                }

                if (cardCount < cardLimit && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << cardCount << _T(" cards, can be ") << cardLimit << _T("]; ");
                }
                if (player.height > heightMid_vgl && player.height < heightTallGK_vgl)
                {
                    errorTot++;
                    errorMsg << _T("GKs in this bracket must be ") << heightTallGK_vgl << _T("cm; ");
                }
            }
            else
            {
                cardMod += min(regCOM_vgl, numCom); //0 free COM styles
                cardMod += min(regTrickCards_vgl, numTrick); //2 free tricks
                //cardMod += min(1, (countA - 1)); //1 free A-position
                cardLimit = regSkillCards_vgl + cardMod; //3 skill cards
                if (cardCount > cardLimit)
                {
                    errorTot++;
                    errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
                }

                if (cardCount < cardLimit && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << cardCount << _T(" cards, can be ") << cardLimit << _T("]; ");
                }
            }

            if (rating == targetRate && player.height < heightManlet_vgl) { //If the player is a manlet and doesn't have the manlet bonus
                manlets_without_bonus.push_back(player);
            }

            if (rating != targetRate)
            {
                if (rating == targetRate + manletBonus_vgl && player.height <= heightManlet_vgl)
                {
                    usingPurple = true;
                    targetRate += manletBonus_vgl;
                    targetRate2 += manletBonus_vgl;
                }
                else
                {
                    errorTot++;
                    errorMsg << _T("Illegal Ability scores; ");
                }
            }

            if (player.injury + 1 != regIR_vgl)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << regIR_vgl << _T("; ");
            }
        }
        /* SILVER */
        else if (rating < goldRate_vgl - goldGiantPen_vgl) //Silver player
        {
            numSilver_vgl++;
            targetRate = silverRate_vgl;
            targetRate2 = silverRate_vgl;

            /*if(player.weak_use+1 != 4)
            {
                errorTot++;
                errorMsg << _T("Weak foot usage is not 4; ");
            }
            if(player.weak_acc+1 != 4)
            {
                errorTot++;
                errorMsg << _T("Weak foot accuracy is not 4; ");
            }*/

            if (player.weak_use + 1 < 4 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Weak foot usage < 4]; ");
            }
            if (player.weak_acc + 1 < 4 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Weak foot accuracy < 4]; ");
            }

            if (numSilver_vgl > reqNumSilver_vgl)
            {
                errorTot++;
                errorMsg << _T("Too many Silver medals; ");
            }

            if (player.form + 1 != silverForm_vgl)
            {
                errorTot++;
                errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << silverForm_vgl << _T("; ");
            }
            if (player.reg_pos == 0) //Medals can't be GK
            {
                errorTot++;
                errorMsg << _T("Medals cannot play as GK; ");
            }
            if (player.height == heightGiant_vgl) //HA get penalty
            {
                targetRate -= silverGiantPen_vgl;
                targetRate2 -= silverGiantPen_vgl;
            }
            else if (player.height <= heightManlet_vgl && rating == targetRate + silverManletBonus_vgl)
            {
                usingPurple = true;
                targetRate += silverManletBonus_vgl;
                targetRate2 += silverManletBonus_vgl;
            }
            if (isManlet) {
                if (countA > manletA_vgl) {
                    cardMod -= (countA - manletA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < manletA_vgl && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << manletA_vgl << _T("]; ");
                }
            }
            else {
                if (countA > silverA_vgl) {
                    cardMod -= (countA - silverA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < silverA_vgl && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << silverA_vgl << _T("]; ");
                }
            }
            cardMod += min(silverTrickCards_vgl, numTrick); //3 free tricks
            cardMod += min(silverCOM_vgl, numCom); //1 free COM
            //cardMod += min(1, (countA - 1)); //1 free A-position
            cardLimit = silverSkillCards_vgl + cardMod; //4 skill cards
            if (cardCount > cardLimit)
            {
                errorTot++;
                errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
            }

            if (numCom < silverCOM_vgl && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << numCom << _T(" COM, can be ") << silverCOM_vgl << _T("]; ");
            }

            if (cardCount < cardLimit && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << cardCount << _T(" cards, can be ") << cardLimit << _T("]; ");
            }

            if (rating != targetRate)
            {
                errorTot++;
                errorMsg << _T("Illegal Ability scores; ");
            }
            if (player.injury + 1 != silverIR_vgl)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << silverIR_vgl << _T("; ");
            }
        }
        /* GOLD */
        else //rating == 99 //Gold player
        {
            numGold_vgl++;
            targetRate = goldRate_vgl;
            targetRate2 = goldRate_vgl;

            /*if(player.weak_use+1 != 4)
            {
                errorTot++;
                errorMsg << _T("Weak foot usage is not 4; ");
            }
            if(player.weak_acc+1 != 4)
            {
                errorTot++;
                errorMsg << _T("Weak foot accuracy is not 4; ");
            }*/

            if (player.weak_use + 1 < 4 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Weak foot usage < 4]; ");
            }
            if (player.weak_acc + 1 < 4 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Weak foot accuracy < 4]; ");
            }

            if (numGold_vgl > reqNumGold_vgl)
            {
                errorTot++;
                errorMsg << _T("Too many Gold medals; ");
            }
            if (player.form + 1 != goldForm_vgl)
            {
                errorTot++;
                errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << goldForm_vgl << _T("; ");
            }
            if (player.reg_pos == 0) //Medals can't be GK
            {
                errorTot++;
                errorMsg << _T("Medals cannot play as GK; ");
            }
            if (player.height == heightGiant_vgl) //Medal HA penalty
            {
                targetRate -= goldGiantPen_vgl;
                targetRate2 -= goldGiantPen_vgl;
            }

            if (isManlet) {
                if (countA > manletA_vgl) {
                    cardMod -= (countA - manletA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < manletA_vgl && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << manletA_vgl << _T("]; ");
                }
            }
            else {
                if (countA > goldA_vgl) {
                    cardMod -= (countA - goldA_vgl); //For VGL: trade A pos for a card
                }

                if (countA < goldA_vgl && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << goldA_vgl << _T("]; ");
                }
            }

            cardMod += min(goldTrickCards_vgl, numTrick); //4 free tricks
            cardMod += min(goldCOM_vgl, numCom); //2 free COMs
            cardLimit = goldSkillCards_vgl + cardMod; //5 skill cards
            if (cardCount > cardLimit)
            {
                errorTot++;
                errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
            }

            if (numCom < goldCOM_vgl && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << numCom << _T(" COM, can be ") << goldCOM_vgl << _T("]; ");
            }

            if (cardCount < cardLimit && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << cardCount << _T(" cards, can be ") << cardLimit << _T("]; ");
            }

            if (rating != targetRate)
            {
                errorTot++;
                errorMsg << _T("Illegal Ability scores; ");
            }

            if (player.injury + 1 > goldIR_vgl)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << goldIR_vgl << _T("; ");
            }
        }

        //Check PES skill card limit of 10
        //if(cardCount-numCom > 10)
        //{
        //    errorTot++;
        //	errorMsg << _T("Has ") << cardCount-numCom << _T(" skill cards, PES limit is 10, please swap to COM cards or trade for additional A positions; ");
        //}

        if (player.drib != targetRate)
        {
            errorTot++;
            errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.gk != targetRate)
        {
            errorTot++;
            errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.finish != targetRate2)
        {
            errorTot++;
            errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetRate2 << _T("; ");
        }
        if (player.lowpass != targetRate)
        {
            errorTot++;
            errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.loftpass != targetRate)
        {
            errorTot++;
            errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.header != targetRate2)
        {
            errorTot++;
            errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetRate2 << _T("; ");
        }
        if (player.swerve != targetRate)
        {
            errorTot++;
            errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.catching != targetRate)
        {
            errorTot++;
            errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.clearing != targetRate)
        {
            errorTot++;
            errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.reflex != targetRate)
        {
            errorTot++;
            errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.body_ctrl != targetRate)
        {
            errorTot++;
            errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.phys_cont != targetRate && pesVersion != 16) //Not in 16
        {
            errorTot++;
            errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.kick_pwr != targetRate)
        {
            errorTot++;
            errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.exp_pwr != targetRate)
        {
            errorTot++;
            errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.ball_ctrl != targetRate)
        {
            errorTot++;
            errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.ball_win != targetRate)
        {
            errorTot++;
            errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.jump != targetRate)
        {
            errorTot++;
            errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.cover != targetRate)
        {
            errorTot++;
            errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.place_kick != targetRate)
        {
            errorTot++;
            errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.stamina != targetRate)
        {
            errorTot++;
            errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.speed != targetRate)
        {
            errorTot++;
            errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetRate << _T("; ");
        }
        if (player.atk > targetRate)
        {
            errorTot++;
            errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", should be ") << targetRate << _T(" or less; ");
        }
        if (player.def > targetRate)
        {
            errorTot++;
            errorMsg << _T("Defensive Prowess is ") << player.def << _T(", should be ") << targetRate << _T(" or less; ");
        }
        if (pesVersion > 19 && player.tight_pos != targetRate)
        {
            errorTot++;
            errorMsg << _T("Tight Possession is ") << player.tight_pos << _T(", should be ") << targetRate << _T("; ");
        }
        if (pesVersion > 19 && player.aggres != targetRate)
        {
            errorTot++;
            errorMsg << _T("Aggression is ") << player.aggres << _T(", should be ") << targetRate << _T("; ");
        }
        if (errorMsg.rdbuf()->in_avail())
        {
            errorMsg << _T("\r\n");
            msgOut += _T("\t");
            msgOut += errorMsg.str();
        }

        if (suggestionMsg.rdbuf()->in_avail() && useSuggestions)
        {
            suggestionMsg << _T("\r\n");
            msgOut += _T("\t");
            msgOut += suggestionMsg.str();
        }
    }
    //Team level errors
    int diff;
    tstringstream errorMsg;
    tstringstream suggestionMsg;
    //Check heights
    if (!usingPurple) //Using Blue height system
    {
        msgOut += _T("Using Blue height system\r\n");
        if (diff = blueColossal_vgl - numColossal_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numColossal_vgl << _T("/") << blueColossal_vgl << _T(" ") << heightColossal_vgl << _T("cm players; ");
        }
        if (diff = blueGiant_vgl - numGiant_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numGiant_vgl << _T("/") << blueGiant_vgl << _T(" ") << heightGiant_vgl << _T("cm players; ");
        }
        if (diff = blueTall_vgl - numTall_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numTall_vgl << _T("/") << blueTall_vgl << _T(" ") << heightTall_vgl << _T("/") << heightTallGK_vgl << _T("cm players; ");
        }
        if (diff = blueMid_vgl - numMid_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numMid_vgl << _T("/") << blueMid_vgl << _T(" ") << heightMid_vgl << _T("cm players; ");
        }
        if (diff = blueManlet_vgl - numManlet_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numManlet_vgl << _T("/") << blueManlet_vgl << _T(" ") << heightManlet_vgl << _T("cm players; ");
        }
    }
    else //Using purple height system
    {
        msgOut += _T("Using Purple height system\r\n");
        if (diff = purpleColossal_vgl - numColossal_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorTot += diff;
            errorMsg << _T("Has ") << numColossal_vgl << _T("/") << purpleColossal_vgl << _T(" ") << heightColossal_vgl << _T("cm players; ");
        }
        if (diff = purpleGiant_vgl - numGiant_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorTot += diff;
            errorMsg << _T("Has ") << numGiant_vgl << _T("/") << purpleGiant_vgl << _T(" ") << heightGiant_vgl << _T("cm players; ");
        }
        if (diff = purpleTall_vgl - numTall_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numTall_vgl << _T("/") << purpleTall_vgl << _T(" ") << heightTall_vgl << _T("/") << heightTallGK_vgl << _T("cm players; ");
        }
        if (diff = purpleMid_vgl - numMid_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numMid_vgl << _T("/") << purpleMid_vgl << _T(" ") << heightMid_vgl << _T("cm players; ");
        }
        if (diff = purpleManlet_vgl - numManlet_vgl)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numManlet_vgl << _T("/") << purpleManlet_vgl << _T(" ") << heightManlet_vgl << _T("cm players; ");
        }
        std::list<player_entry>::iterator it;
        for (it = manlets_without_bonus.begin(); it != manlets_without_bonus.end(); ++it) {
            suggestionTot++;
            suggestionMsg << _T("[Player ") << it->name << _T(" is a manlet and can have ") << regRate_vgl + manletBonus_vgl << _T(" rating]; \r\n");
        }
    }
    if (errorMsg.rdbuf()->in_avail())
    {
        errorMsg << _T("\r\n");
        msgOut += errorMsg.str();
        errorMsg.clear();
        errorMsg.str(tstring());
    }

    //Check ability stats
    if (numReg_vgl != (23 - reqNumSilver_vgl - reqNumGold_vgl))
    {
        errorTot++;
        errorMsg << _T("Number of Regular players is ") << numReg_vgl << _T(", should be ") << 23 - reqNumSilver_vgl - reqNumGold_vgl << _T("; ");
    }
    if (numSilver_vgl != reqNumSilver_vgl)
    {
        errorTot++;
        errorMsg << _T("Number of Silver medals is ") << numSilver_vgl << _T(", should be ") << reqNumSilver_vgl << _T("; ");
    }
    if (numGold_vgl != reqNumGold_vgl)
    {
        errorTot++;
        errorMsg << _T("Number of Gold medals is ") << numGold_vgl << _T(", should be ") << reqNumGold_vgl << _T("; ");
    }
    if (errorMsg.rdbuf()->in_avail())
        errorMsg << _T("\r\n");
    errorMsg << _T("\r\nErrors: ") << errorTot << _T("\r\n\r\n");
    msgOut += errorMsg.str();

    if (!captainHasCard && useSuggestions) {
        suggestionTot++;
        suggestionMsg << _T("[Captain does not have free captain card]; ");
    }
    if (useSuggestions) {
        suggestionMsg << _T("\r\Suggestions: ") << suggestionTot << _T("\r\n");
        msgOut += suggestionMsg.str();
    }


    SetWindowText(GetDlgItem(hAatfbox, IDT_AATFOUT), msgOut.c_str());
    if (errorTot)
        //SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("It's all so tiresome."));
        SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("It's all fucked."));
    else
        //SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("You have received one (1) Official R-word Pass."));
        SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("Perfect, blaze."));
}
