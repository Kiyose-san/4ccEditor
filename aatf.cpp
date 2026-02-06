#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#include "stats.h"
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

//The following is a list of all the skills and their corresponding IDs
//An * means this is considered a skill card
/*
ID	Name
0	Scissors Feint *
1	Flip Flap *
2	Marseille Turn *
3	Sombrero *
4	Cut Behind & Turn *
5	Scotch Move *
6	Heading
7	Long Range Drive
8	Knuckle Shot
9	Acrobatic Finishing
10	Heel Trick
11	First Time Shot
12	One Shot Pass
13	Weighted Pass
14	Pinpoint Crossing
15	Outside Curler
16	Rabona *
17	Low Lofted Pass
18 	Low Punt Trajectory
19	Long Throw
20	GK Long Throw
21	Malicia *
22	Man Marking
23	Track Back
24	Acrobatic Clear
25	Captaincy
26	Super Sub
27	Fighting Spirit
28	Double Touch *
29	Crossover Turn *
30	Step On Skill *
31	Chip Shot
32	Dipping Shot
33	Rising Shots
34	No Look Pass *
35	High Punt Trajectory
36	Penalty Specialist
37	GK Penalty Specialist
38	Interception
39	Long Range Shooting
40	Through Passing
*/

//============================
//AATF Settings
int manletBonus = 5;
int silverManletBonus = 0;
int goldManletBonus = 0;
int silverGiantPen = 0;
int goldGiantPen = 0;

int goldRate = 99; //Player skill ratings
int silverRate = 88;
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

int goldWeakFootUse = 2; //Gold medal weak foot usage limit
int silverWeakFootUse = 2;
int regWeakFootUse = 2;

int goldWeakFootAcc = 4; //Gold medal weak foot accuracy limit
int silverWeakFootAcc = 4;
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
int greenGiant = 5;
int greenTall = 6;
int greenMid = 6;
int greenManlet = 6;

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

/*
//VGL Settings
int manletBonus_vgl = 5;
int silverManletBonus_vgl = 2;
int goldManletBonus_vgl = 2;
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
int purpleGiant_vgl = 6;
int purpleTall_vgl = 5;
int purpleMid_vgl = 6;
int purpleManlet_vgl = 6;

int heightColossal_vgl = 210;
int heightGiant_vgl = 190;
int heightTall_vgl = 185;
int heightTallGK_vgl = 189;
int heightMid_vgl = 180;
int heightManlet_vgl = 175;

int freeCardOne_vgl = 9;

bool canMedalsBeGiant_vgl = false;
bool canGKBeGiant_vgl = false;

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
*/


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
		if (pesVersion > 15)
		{
			rating = max(player.clearing, rating);
			rating = max(player.reflex, rating);
			rating = max(player.cover, rating);
		}
		rating = max(player.body_ctrl, rating);
		if (pesVersion > 16) rating = max(player.phys_cont, rating); //Not in 16
		rating = max(player.kick_pwr, rating);
		rating = max(player.exp_pwr, rating);
		rating = max(player.ball_ctrl, rating);
		rating = max(player.ball_win, rating);
		rating = max(player.jump, rating);
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
		int countB = 0;
		for (int jj = 0; jj < 13; jj++)
		{
			if (player.play_pos[jj] == 2)
				countA++;
			else if (player.play_pos[jj] == 1)
				countB++;
		}

		//No B positions allowed:
		if (countB > 0)
		{
			errorTot++;
			errorMsg << _T("Has B position; ");
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

		//Check playing style and registered position are in valid range per PES version
		if (player.reg_pos > 12)
		{
			errorTot++;
			errorMsg << _T("Registered position out of range (0-12); ");
		}

		if (pesVersion <= 16)
		{
			if (player.play_style > 18 || player.play_style == 16)
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-18, excluding 16); ");
			}
		}
		else if (pesVersion > 16 && pesVersion < 19)
		{
			if (player.play_style > 17)
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-17); ");
			}
		}
		else
		{
			if (player.play_style > 21)
			{
				errorTot++;
				errorMsg << _T("Playing style out of range (0-21); ");
			}
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

			//SPECIAL FAG13: Medals can trade a card for 4/4 footedness
			/*if (player.weak_use + 1 > weakFootUse)
			{
				weakFootUse = 4;
				cardLimit--;
			}*/
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

			//SPECIAL FAG13: Medals can trade a card for 4/4 footedness
			/*if (player.weak_use + 1 > weakFootUse)
			{
				weakFootUse = 4;
				cardLimit--;
			}*/
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
			if (player.weak_use + 1 < weakFootUse) errorMsg << _T("WARN: Has weak usage ") << player.weak_use + 1 << _T(", allowed ") << weakFootUse << _T("; ");
			if (player.weak_acc + 1 < weakFootAcc) errorMsg << _T("WARN: Has weak accuracy ") << player.weak_acc + 1 << _T(", allowed ") << weakFootAcc << _T("; ");
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
										{player.clearing,	_T("Clearing"),				16,		targetRate	},
										{player.reflex,		_T("Reflexes"),				16,		targetRate	},
										{player.body_ctrl,	_T("Body Control"),			0,		targetRate	},
										{player.phys_cont,	_T("Physical Contact"),		17,		targetRate	},
										{player.kick_pwr,	_T("Kicking Power"),		0,		targetRate	},
										{player.exp_pwr,	_T("Explosive Power"),		0,		targetRate	},
										{player.ball_ctrl,	_T("Ball Control"),			0,		targetRate	},
										{player.ball_win,	_T("Ball Winning"),			0,		targetRate	},
										{player.jump,		_T("Jump"),					0,		targetRate	},
										{player.cover,		_T("Coverage"),				16,		targetRate	},
										{player.place_kick, _T("Place Kicking"),		0,		targetRate	},
										{player.stamina,	_T("Stamina"),				0,		targetRate3	},
										{player.speed,		_T("Speed"),				0,		targetRate	},
										{player.atk,		_T("Attacking Prowess"),	0,		targetRate	},
										{player.def,		_T("Defensive Prowess"),	0,		targetRate2	},
										{player.tight_pos,	_T("Tight Possession"),		20,		targetRate	},
										{player.aggres,		_T("Aggression"),			20,		targetRate	} };

		for (int ii = 0; ii < 25; ii++)
		{
			//atk and def can be lower than the target rate
			if (skillChecks[ii].s_skillName == _T("Attacking Prowess") || skillChecks[ii].s_skillName == _T("Defensive Prowess"))
			{
				if (skillChecks[ii].n_minPesVersion <= pesVersion && skillChecks[ii].c_skillRate > skillChecks[ii].n_targetRate)
				{
					errorTot++;
					errorMsg << skillChecks[ii].s_skillName << _T(" is ") << skillChecks[ii].c_skillRate << _T(", should be <= ") << skillChecks[ii].n_targetRate << _T("; ");
				}
			}
			else if (skillChecks[ii].n_minPesVersion <= pesVersion &&
				skillChecks[ii].c_skillRate != skillChecks[ii].n_targetRate)
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

	int numGK = 0;
	//Count of player ratings
	int numReg = 0;
	int numBuff = 0;
	int numBronze = 0;
	int numSilver = 0;
	int numGold = 0;
	//Count of height brackets
	int numGiga = 0;
	int numGiant = 0;
	int numTall = 0;
	int numMid = 0;
	int numManlet = 0;
	//bool usingRed = true;
	//buff positions used
	int buffPosition1 = -1;
	int buffPosition2 = -1;
	int buffPosition3 = -1;

	int numTrickOrCom = 0;

	int errorTot = 0;
	int suggestionTot = 0;

	int maxCOM = 99;

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
		int comMod = 0;
		int cardMin = 41;
		int cardLimit = 0;
		int heightMod = 0;
		int weakFoot = 2;
		bool hasTrick = false;
		bool hasTrickCom = false;
		int targetRate = 0;
		int rating = player.clearing; //this needs to be a stat that isn't changed from base rates

		/*rating = max(player.gk, rating);
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
		if (pesVersion > 19) rating = max(player.aggres, rating);*/

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
		int numTrickCom = 0;
		int numCom = 0;
		int numSkill = 0;
		bool isCaptain = false;
		int freeCOMs = 0;
		int totalSkills;
		bool NMWMFBuffed = false;
		bool medalCFTBuff = false;
		bool isBronze = false;
		bool isSilver = false;
		bool isGold = false;
		int DFBonus = 0;
		int BEDKSFBonus = 0;
		int DPBonus = 0;
		int GCCRBonus = 0;
		int GCRBonus = 0;
		int FBonus = 0;
		int FDBonus = 0;
		//int OFLLBKBonus = 0;
		int targetDrib = 0;
		int targetGk = 0;
		int targetFinish = 0;
		int targetLowpass = 0;
		int targetLoftpass = 0;
		int targetHeader = 0;
		int targetSwerve = 0;
		int targetCatching = 0;
		int targetClearing = 0;
		int targetReflex = 0;
		int targetBody_ctrl = 0;
		int targetPhys_cont = 0;
		int targetKick_pwr = 0;
		int targetExp_pwr = 0;
		int targetBall_ctrl = 0;
		int targetBall_win = 0;
		int targetJump = 0;
		int targetCover = 0;
		int targetPlace_kick = 0;
		int targetStamina = 0;
		int targetSpeed = 0;
		int targetAtk = 0;
		int targetDef = 0;
		int targetTight_pos = 0;
		int targetAggres = 0;

		int freeAPositions = 0;
		int allowedHeight = 0;

		int regSkillCardsMin = 0;
		int medalSkillCardsMin = 0;


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

				/*if (jj == freeCardOne_vgl)
				{non
					cardMod++;
				}*/

				// Players may have the First-Time Shot and Acrobatic Finishing skill cards for free
				if (jj == 11) { //11 = First-Time Shot
					cardMod++;
				}

				if (jj == 9) { //9 = Acrobatic Finishing
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
		/*
		if (player.id == gteams[teamSel].players[gteams[teamSel].captain_ind]) {
			cardMod++;
		}
		*/

		for (int jj = 0; jj < 7; jj++)
		{
			if (player.com_style[jj])
			{
				cardCount++;
				numCom++;

				//Free COMs
				if (jj == 3) { //3 = Incisive Run
					comMod++;
				}

				if (jj == 6) { //6 = Long Ranger
					comMod++;
				}				
			}
		}

		/*
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

		if ((!canGKBeGiant_vgl) && player.height == heightGiant_vgl && player.reg_pos == 0)
		{
			errorTot++;
			errorMsg << _T("Goalkeeper can't be ") << heightGiant_vgl << _T(";");
		}
		*/

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
		if (player.height == nm::height || player.height == nm::gk_height) //Regular player
		{
			using namespace nm; // all values pulling from the nm namespace
			numReg++;
			targetRate += base_stat;
			cardMin = regSkillCardsMin;

			weakFoot = weak_foot_usage;



			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;
			if (player.reg_pos == 0) //player is a gk, use gk height
			{
				allowedHeight = gk_height;
			}
			/*
			if (isCaptain)
			{
				errorTot++;
				errorMsg << _T("Regulars can't be captain; ");
			}
			*/
			if (player.reg_pos == 0 && player.form + 1 != gk_form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << gk_form << _T("; ");
			}
			else if (player.reg_pos != 0 && player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}


			/*if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}*/

			//cardMod += min(nm::free_coms, numCom-numTrickCom); 
			cardMod += numTrick;
			cardLimit = skills + cardMod;
			freeCOMs = nm::free_coms + comMod;

			/*if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				NMWMFBuffed = true;
				numNMWMFBuffEligible++;
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}*/
		}
		/* Buffed */
		else if (player.height == buffed::height) //buffed player
		{
			using namespace buffed; // all values pulling from the buffed namespace
			numBuff++;
			targetRate += base_stat;
			cardMin = regSkillCardsMin;

			weakFoot = weak_foot_usage;
			if (player.play_pos[10] == 2 || player.play_pos[11] == 2 || player.play_pos[6] == 2 || player.play_pos[5] == 2) //playable at LB, RB, CMF, or DMF
			{
				weakFoot = weak_foot_usage_debuff;
			}

			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;
			if (buffPosition1 == -1)
			{
				buffPosition1 = player.reg_pos;
			}
			else if (buffPosition1 != player.reg_pos && buffPosition2 == -1)
			{
				buffPosition2 = player.reg_pos;
			}
			else if (player.reg_pos != buffPosition1 && player.reg_pos != buffPosition2 && buffPosition3 == -1)
			{
				buffPosition3 = player.reg_pos;
				//this will output a team level error later
			}

			/*
			if (isCaptain)
			{
				errorTot++;
				errorMsg << _T("Regulars can't be captain; ");
			}
			*/

			/*
			if (player.reg_pos == 0 || player.reg_pos == 1 || player.reg_pos == 9 || player.reg_pos == 10 || player.reg_pos == 12)
			{
				errorTot++;
				errorMsg << _T("Only LB, RB, DMF, LMF, RMF, CMF, AMF, or SS registered position players can be buffed; ");
			}
			*/
			if (player.play_pos[9] == 2)
			{
				errorTot++;
				errorMsg << _T("Buffed players may not have an A-position at CB; ");
			}
			else if (player.reg_pos != 0 && player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}

			for (int jj = 0; jj < numSkill; jj++)
			{
				if (player.play_skill[jj])
				{
					// Buffed players may have the Weighted Pass and One-Touch Pass skill cards for free
					if (jj == 13) { //13 = Weighted Pass
						cardMod++;
					}

					if (jj == 12) { //12 = One-Touch Pass
						cardMod++;
					}
				}
			}


			/*if (countA > 1)
			{
				errorTot++;
				errorMsg << _T("Only 1 A position for non-medals;");
			}*/

			//cardMod += min(buffed::free_coms, numCom-numTrickCom);
			cardMod += numTrick;
			cardLimit = skills + cardMod;
			freeCOMs = buffed::free_coms + comMod;

			/*if (numCom > regCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << regCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 6 || player.reg_pos == 7 || player.reg_pos == 9 || player.reg_pos == 10)
			{
				NMWMFBuffed = true;
				numNMWMFBuffEligible++;
				heightMod += regWMFHeightBonus;
				targetRate += regWMFStatBonus;
			}*/
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Buffed cannot play as GK; ");
			}
		}
		/* BRONZE */
		else if (player.height == bronze::height && player.aggres == bronze::aggression) //Bronze player
		{
			using namespace bronze; //all stats pulled from bronze namespace
			isBronze = true;
			numBronze++;
			targetRate += base_stat;
			cardMin = medalSkillCardsMin;

			weakFoot = weak_foot_usage;

			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;

			if (numBronze > bronze::count)
			{
				errorTot++;
				errorMsg << _T("Too many Bronze medals; ");
			}
			if (player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}

			/*if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}*/

			cardMod += numTrick;
			//cardMod += min(free_coms, numCom-numTrickCom); 
			cardLimit = skills + cardMod;
			freeCOMs = bronze::free_coms + comMod;

			/*if (numCom > bronzeCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << bronzeCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 9 || player.reg_pos == 10)
			{
				heightMod += bronzeWFHeightBonus;
				targetRate += bronzeWFStatBonus;
			}*/

			/*if (player.reg_pos == 12 && (player.play_style == 3 || player.play_style == 13))
			{
				heightMod += medalCFTFHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}*/
		}
		/* SILVER */
		else if (player.height == silver::height) //Silver player
		{
			using namespace silver; //all stats pulled from silver namespace
			isSilver = true;
			numSilver++;
			targetRate += base_stat;
			cardMin = medalSkillCardsMin;

			weakFoot = weak_foot_usage;

			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;

			if (numSilver > silver::count)
			{
				errorTot++;
				errorMsg << _T("Too many Silver medals; ");
			}
			if (player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}

			/*if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}*/

			cardMod += numTrick;
			//cardMod += min(free_coms, numCom-numTrickCom); 
			cardLimit = skills + cardMod;
			freeCOMs = silver::free_coms + comMod;

			/*if (numCom > silverCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << silverCOM << _T("; ");
			}*/

			if (player.injury + 1 != injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 9 || player.reg_pos == 10)
			{
				heightMod += silverWFHeightBonus;
				targetRate += silverWFStatBonus;
			}*/

			/*if (player.reg_pos == 12 && (player.play_style == 3 || player.play_style == 13))
			{
				heightMod += medalCFTFHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}*/
		}
		/* GOLD */
		else if (player.height == gold::height) //Gold player
		{
			using namespace gold;
			isGold = true;
			numGold++;
			targetRate += base_stat;
			cardMin = medalSkillCardsMin;

			weakFoot = weak_foot_usage;

			if (numGold > gold::count)
			{
				errorTot++;
				errorMsg << _T("Too many Gold medals; ");
			}
			if (player.form + 1 != form)
			{
				errorTot++;
				errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << form << _T("; ");
			}
			if (player.reg_pos == 0) //Medals can't be GK
			{
				errorTot++;
				errorMsg << _T("Medals cannot play as GK; ");
			}

			/*if (countA > 2)
			{
				errorTot++;
				errorMsg << _T("Only 2 A positions for medals;");
			}*/
			//set the targets to the namespace values. note some of these are 0 as they should be base rate
			targetDrib = dribbling;
			targetGk = gk_awareness;
			targetFinish = finishing;
			targetLowpass = low_pass;
			targetLoftpass = lofted_pass;
			targetHeader = header;
			targetSwerve = curl;
			targetCatching = catching;
			targetClearing = clearing;
			targetReflex = reflexes;
			targetBody_ctrl = balance;
			targetPhys_cont = physical_contact;
			targetKick_pwr = kicking_power;
			targetExp_pwr = acceleration;
			targetBall_ctrl = ball_control;
			targetBall_win = ball_winning;
			targetJump = jump;
			targetCover = gk_reach;
			targetPlace_kick = place_kicking;
			targetStamina = stamina;
			targetSpeed = speed;
			targetAtk = offensive_awareness;
			targetDef = defensive_awareness;
			targetTight_pos = tight_possession;
			targetAggres = aggression;
			//fix all the 0 values and make them the base rate
			if (targetDrib == 0)
			{
				targetDrib = base_stat;
			}
			if (targetGk == 0)
			{
				targetGk = base_stat;
			}
			if (targetFinish == 0)
			{
				targetFinish = base_stat;
			}
			if (targetLowpass == 0)
			{
				targetLowpass = base_stat;
			}
			if (targetLoftpass == 0)
			{
				targetLoftpass = base_stat;
			}
			if (targetHeader == 0)
			{
				targetHeader = base_stat;
			}
			if (targetSwerve == 0)
			{
				targetSwerve = base_stat;
			}
			if (targetCatching == 0)
			{
				targetCatching = base_stat;
			}
			if (targetClearing == 0)
			{
				targetClearing = base_stat;
			}
			if (targetReflex == 0)
			{
				targetReflex = base_stat;
			}
			if (targetBody_ctrl == 0)
			{
				targetBody_ctrl = base_stat;
			}
			if (targetPhys_cont == 0)
			{
				targetPhys_cont = base_stat;
			}
			if (targetKick_pwr == 0)
			{
				targetKick_pwr = base_stat;
			}
			if (targetExp_pwr == 0)
			{
				targetExp_pwr = base_stat;
			}
			if (targetBall_ctrl == 0)
			{
				targetBall_ctrl = base_stat;
			}
			if (targetBall_win == 0)
			{
				targetBall_win = base_stat;
			}
			if (targetJump == 0)
			{
				targetJump = base_stat;
			}
			if (targetCover == 0)
			{
				targetCover = base_stat;
			}
			if (targetPlace_kick == 0)
			{
				targetPlace_kick = base_stat;
			}
			if (targetStamina == 0)
			{
				targetStamina = base_stat;
			}
			if (targetSpeed == 0)
			{
				targetSpeed = base_stat;
			}
			if (targetAtk == 0)
			{
				targetAtk = base_stat;
			}
			if (targetDef == 0)
			{
				targetDef = base_stat;
			}
			if (targetTight_pos == 0)
			{
				targetTight_pos = base_stat;
			}
			if (targetAggres == 0)
			{
				targetAggres = base_stat;
			}

			freeAPositions = free_a;

			allowedHeight = height;

			cardMod += numTrick;
			//cardMod += min(free_coms, numCom-numTrickCom); 
			cardLimit = skills + cardMod;
			freeCOMs = gold::free_coms + comMod;

			/*if (numCom > goldCOM)
			{
				errorTot++;
				errorMsg << _T("Has ") << numCom << _T(" COM playing styles, should be no more than ") << goldCOM << _T("; ");
			}*/

			if (player.injury + 1 > injury_resistance)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << injury_resistance << _T("; ");
			}

			/*if (player.reg_pos == 12 && player.play_style == 13)
			{
				heightMod += medalCFTHeightBonus;
				if (player.play_style == 13)
				{
					medalCFTBuff = true;
				}
			}*/
		}
		else {
			errorTot++;
			errorMsg << _T("Illegal Ability scores, this player's height does not match any available player types; "); //mentions that height is what is being checked
			//spit out whatever errors were already found, but target scores can't be set, so quit out of this player to avoid useless error outputs
			errorMsg << _T("\r\n");
			msgOut += _T("\t");
			msgOut += errorMsg.str();
			continue;
		}

		if (player.height != allowedHeight)
		{
			errorTot++;
			errorMsg << _T("Wrong height, allowed height is: ") << allowedHeight << _T("; ");
		}

		int neutralModHeight = player.height - heightMod;
		//int debuffedModHeight = player.height - heightMod + regWMFHeightBonus;
		int confirmedNMWMFBuff = false;


		/*if (medalCFTBuff)
		{
			weakFoot = medalCFTFootedness;
		}*/

		//Check weak foot ratings
		if (player.weak_use + 1 > weakFoot)
		{
			errorTot++;
			errorMsg << _T("Weak foot usage > ") << weakFoot << _T("; ");
		}
		if (player.weak_acc + 1 > weakFoot)
		{
			errorTot++;
			errorMsg << _T("Weak foot accuracy > ") << weakFoot << _T("; ");
		}

		int amountOfCOMs = numCom - numTrickCom;
		int maxAmountOfCOMs = freeCOMs; //Includes comMod
		int skillCardCountWithoutCOMsAndMod = (cardCount - numCom) - cardMod;

		//Check player skill card count
		if ((skillCardCountWithoutCOMsAndMod + cardMod) - numTrick > cardLimit - numTrick) //don't include trick cards in either count
		{
			errorTot++;
			errorMsg << _T("Has ") << (skillCardCountWithoutCOMsAndMod + cardMod) - numTrick << _T(" non-free skill cards, only allowed ") << cardLimit - numTrick << _T("; ");
		}

		//If there are more than the max amount of COMs
		if (amountOfCOMs > maxAmountOfCOMs) {
			int tooManyAmountOfComs = (numCom - numTrickCom) - freeCOMs;
			int amountOfSkillCardAllowance = (cardLimit - cardMod) - skillCardCountWithoutCOMsAndMod;
			if (tooManyAmountOfComs > amountOfSkillCardAllowance) {
				errorMsg << _T("Has ") << numCom - numTrickCom << _T(" non-free COM styles, only allowed ") << freeCOMs + max(0, (cardLimit - cardCount)) << _T(". Remove non-free skill cards to add COM styles; ");
			}
		}


		/*
		//Check player skill card count
		if ((cardCount - numTrick)  > ((cardLimit + comMod) - numTrick) - (freeCOMs - numCom)) //don't include trick cards in either count
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numTrick << _T(" non-free skill cards, only allowed ") << ((cardLimit + comMod) - numTrick) - (freeCOMs - numCom) << _T("; ");
		}

		int amountOfCOMs = numCom - numTrickCom;
		int maxAmountOfCOMs = freeCOMs + comMod;
		int skillCardCountWithoutCOMs = cardCount - numCom;

		//If there are more than the max amount of COMs
		if (amountOfCOMs > maxAmountOfCOMs) {
			int tooManyAmountOfComs = (numCom - numTrickCom) - freeCOMs + comMod;
			int amountOfSkillCardAllowance = cardLimit - skillCardCountWithoutCOMs;
			if (tooManyAmountOfComs > amountOfSkillCardAllowance) {
				errorMsg << _T("Has ") << numCom - numTrickCom << _T(" non-free COM styles, only allowed ") << freeCOMs + max(0, (cardLimit - cardCount)) << _T(". Remove non-free skill cards to add COM styles; ");
			}
		}*/

		/*
		//Check player com style count
		if ((numCom - numTrickCom) > (freeCOMs + max(0, (cardLimit - (cardCount - numCom))))) //unused skill cards can be exchanged for com styles, don't include free com styles
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom - numTrickCom << _T(" non-free COM styles, only allowed ") << freeCOMs + max(0, (cardLimit - cardCount)) << _T(". Remove non-free skill cards to add COM styles; ");
		}
		*/

		/*errorMsg << _T("Has ") << confirmedNMWMFBuff << (player.reg_pos == 9) << player.play_pos[8];
		errorMsg << _T("Has ") << player.play_pos[0];CF
		errorMsg << _T("Has ") << player.play_pos[1];SS
		errorMsg << _T("Has ") << player.play_pos[2];LWF
		errorMsg << _T("Has ") << player.play_pos[3];RWF
		errorMsg << _T("Has ") << player.play_pos[4];AMF
		errorMsg << _T("Has ") << player.play_pos[5];DMF
		errorMsg << _T("Has ") << player.play_pos[6];CMF
		errorMsg << _T("Has ") << player.play_pos[7];LMF
		errorMsg << _T("Has ") << player.play_pos[8];RMF
		errorMsg << _T("Has ") << player.play_pos[9];CB
		errorMsg << _T("Has ") << player.play_pos[10];LB
		errorMsg << _T("Has ") << player.play_pos[11];RB
		errorMsg << _T("Has ") << player.play_pos[12];GK*/

		int cardsSwappedForAPositions = countA - freeAPositions;
		bool usingNMWMFAPos = confirmedNMWMFBuff && (
			(player.reg_pos == 6 && player.play_pos[2] == 2) ||
			(player.reg_pos == 7 && player.play_pos[3] == 2) ||
			(player.reg_pos == 9 && player.play_pos[7] == 2) ||
			(player.reg_pos == 10 && player.play_pos[8] == 2)
			);

		if (confirmedNMWMFBuff)
		{
			if (player.play_pos[9] == 2 || player.play_pos[10] == 2 || player.play_pos[11] == 2)
			{
				errorTot++;
				errorMsg << _T("No LB, CB or RB A positions for buffed LWF, RWF, LMF, RMF non-medals; ");
			}
		}

		if (usingNMWMFAPos)
		{
			cardsSwappedForAPositions--;
		}

		if (countA > freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))))
		{
			if (usingNMWMFAPos)
			{
				if (countA > freeAPositions + max(0, cardLimit - cardCount) + 1)
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount) + 1 << _T(". Remove cards to add A position slots; ");
				}
			}
			else if (countA > freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))))
			{
				if (max(0, ((numCom - numTrickCom) - freeCOMs)) == 0) //hasn't exchanged any skill cards for com styles
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))) << _T(". Remove non-free skill cards to add A position slots; ");
				}
				else //exchanged at least 1 skill card for a com style
				{
					errorTot++;
					errorMsg << _T("Has ") << countA << _T(" A positions, only allowed ") << freeAPositions + max(0, cardLimit - cardCount - max(0, ((numCom - numTrickCom) - freeCOMs))) << _T(". Remove non-free skill cards or up to ") << (numCom - numTrickCom) - freeCOMs << _T(" non-free COM style(s) to add A position slots; ");
				}
			}
		}

		if (player.reg_pos == 0 || cardsSwappedForAPositions < 0)
		{
			cardsSwappedForAPositions = 0;
		}


		if (cardCount - numTrick < cardMin - cardsSwappedForAPositions)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount - numTrick << _T(" skill cards, must have at least ") << cardMin - cardsSwappedForAPositions << _T("; ");
			//errorMsg << cardCount << min(freeCOMs, numCom) << numTrick;
		}

		//Check PES skill card limit of 10
		//21 apparently can load over 10 cards, limit is set at 11 now.
		/*
		
		if (cardCount > 11)
		{
			errorTot++;
			errorMsg << _T("Has ") << cardCount << _T(" skill cards, only allowed 11; ");
		}
		*/

		//Check COM hard cap
		if (numCom > maxCOM)
		{
			errorTot++;
			errorMsg << _T("Has ") << numCom << _T(" COM playing styles, limit is ") << maxCOM << _T("; ");
		}

		/*if (NMWMFBuffed && !confirmedNMWMFBuff) {
			targetRate -= regWMFStatBonus;
		}
		*/
		//Check player overall rating
		if (rating != targetRate)
		{
			errorTot++;
			errorMsg << _T("Illegal Ability scores; ");
		}

		//Check individual skill ratings

		if (player.drib != targetDrib)
		{
			errorTot++;
			errorMsg << _T("Dribbling is ") << player.drib << _T(", should be ") << targetDrib << _T("; ");
		}
		if (player.gk != targetGk)
		{
			errorTot++;
			errorMsg << _T("Goalkeeping is ") << player.gk << _T(", should be ") << targetGk << _T("; ");
		}
		if (player.finish != targetFinish)
		{
			errorTot++;
			errorMsg << _T("Finishing is ") << player.finish << _T(", should be ") << targetFinish << _T("; ");
		}
		if (player.lowpass != targetLowpass)
		{
			errorTot++;
			errorMsg << _T("Low Pass is ") << player.lowpass << _T(", should be ") << targetLowpass << _T("; ");
		}
		if (player.loftpass != targetLoftpass)
		{
			errorTot++;
			errorMsg << _T("Lofted Pass is ") << player.loftpass << _T(", should be ") << targetLoftpass << _T("; ");
		}
		if (player.header != targetHeader)
		{
			errorTot++;
			errorMsg << _T("Header is ") << player.header << _T(", should be ") << targetHeader << _T("; ");
		}
		if (player.swerve != targetSwerve)
		{
			errorTot++;
			errorMsg << _T("Swerve is ") << player.swerve << _T(", should be ") << targetSwerve << _T("; ");
		}
		if (player.catching != targetCatching)
		{
			errorTot++;
			errorMsg << _T("Catching is ") << player.catching << _T(", should be ") << targetCatching << _T("; ");
		}
		if (player.clearing != targetClearing)
		{
			errorTot++;
			errorMsg << _T("Clearing is ") << player.clearing << _T(", should be ") << targetClearing << _T("; ");
		}
		if (player.reflex != targetReflex)
		{
			errorTot++;
			errorMsg << _T("Reflexes is ") << player.reflex << _T(", should be ") << targetReflex << _T("; ");
		}
		if (player.body_ctrl != targetBody_ctrl)
		{
			errorTot++;
			errorMsg << _T("Body Control is ") << player.body_ctrl << _T(", should be ") << targetBody_ctrl << _T("; ");
		}
		if (player.phys_cont != targetPhys_cont && pesVersion != 16) //Not in 16
		{
			errorTot++;
			errorMsg << _T("Physical Contact is ") << player.phys_cont << _T(", should be ") << targetPhys_cont << _T("; ");
		}
		if (player.kick_pwr != targetKick_pwr)
		{
			errorTot++;
			errorMsg << _T("Kicking Power is ") << player.kick_pwr << _T(", should be ") << targetKick_pwr << _T("; ");
		}
		if (player.exp_pwr != targetExp_pwr)
		{
			errorTot++;
			errorMsg << _T("Explosive Power is ") << player.exp_pwr << _T(", should be ") << targetExp_pwr << _T("; ");
		}
		if (player.ball_ctrl != targetBall_ctrl)
		{
			errorTot++;
			errorMsg << _T("Ball Control is ") << player.ball_ctrl << _T(", should be ") << targetBall_ctrl << _T("; ");
		}
		if (player.ball_win != targetBall_win)
		{
			errorTot++;
			errorMsg << _T("Ball winning is ") << player.ball_win << _T(", should be ") << targetBall_win << _T("; ");
		}
		if (player.jump != targetJump)
		{
			errorTot++;
			errorMsg << _T("Jump is ") << player.jump << _T(", should be ") << targetJump << _T("; ");
		}
		if (player.cover != targetCover)
		{
			errorTot++;
			errorMsg << _T("Coverage is ") << player.cover << _T(", should be ") << targetCover << _T("; ");
		}
		if (player.place_kick != targetPlace_kick)
		{
			errorTot++;
			errorMsg << _T("Place Kicking is ") << player.place_kick << _T(", should be ") << targetPlace_kick << _T("; ");
		}
		if (player.stamina != targetStamina)
		{
			errorTot++;
			errorMsg << _T("Stamina is ") << player.stamina << _T(", should be ") << targetStamina << _T("; ");
		}
		if (player.speed != targetSpeed)
		{
			errorTot++;
			errorMsg << _T("Speed is ") << player.speed << _T(", should be ") << targetSpeed << _T("; ");
		}
		if (player.atk > targetAtk) //NOTE: can be lower 
		{
			errorTot++;
			errorMsg << _T("Attacking Prowess is ") << player.atk << _T(", may not be higher than ") << targetAtk << _T("; ");
		}
		if (player.def > targetDef) //NOTE: can be lower 
		{
			errorTot++;
			errorMsg << _T("Defensive Prowess is ") << player.def << _T(", may not be higher than ") << targetDef << _T("; ");
		}
		if (pesVersion > 19 && player.tight_pos != targetTight_pos)
		{
			errorTot++;
			errorMsg << _T("Tight Possession is ") << player.tight_pos << _T(", should be ") << targetTight_pos << _T("; ");
		}
		if (pesVersion > 19 && player.aggres != targetAggres)
		{
			errorTot++;
			errorMsg << _T("Aggression is ") << player.aggres << _T(", should be ") << targetAggres << _T("; ");
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
		/*
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
		*/
	}
	else //Using purple height system
	{
		/*
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
		*/
	}
	if (errorMsg.rdbuf()->in_avail())
	{
		errorMsg << _T("\r\n");
		msgOut += errorMsg.str();
		errorMsg.clear();
		errorMsg.str(tstring());
	}

	//Check ability stats
	if (numReg != nm::count)
	{
		errorTot++;
		errorMsg << _T("Number of Regular players is ") << numReg << _T(", should be ") << nm::count << _T("; ");
	}
	if (numBuff != buffed::count)
	{
		errorTot++;
		errorMsg << _T("Number of Buffed players is ") << numBuff << _T(", should be ") << buffed::count << _T("; ");
	}
	if (numSilver != silver::count)
	{
		errorTot++;
		errorMsg << _T("Number of Silver medals is ") << numSilver << _T(", should be ") << silver::count << _T("; ");
	}
	if (numGold != gold::count)
	{
		errorTot++;
		errorMsg << _T("Number of Gold medals is ") << numGold << _T(", should be ") << gold::count << _T("; ");
	}
	/*
	if (buffPosition3 != -1)
	{
		errorTot++;
		errorMsg << _T("Too many registered positions with buffed players. Maximum is 2; ");
	}
	*/
	//check that there are no nonbuffed nonmedal players in registered positions that are buffed
	/*
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
		if ((player.reg_pos == buffPosition1 || player.reg_pos == buffPosition2) && player.height == nm::height)
		{
			errorTot++;
			errorMsg << _T("Player ") << player.name << _T(" has the same registererd position as a buffed player, but isn't a buffed non-medal; ");
		}

	}
	*/
	if (pesVersion == 16)
	{
		for (int ii = 0; ii < 11; ii++)
		{
			if (gteams[teamSel].ManMarking1[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 1; ");
				break;

			}
		}
		for (int ii = 0; ii < 11; ii++)
		{
			if (gteams[teamSel].ManMarking2[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 2; ");
				break;

			}
		}
		for (int ii = 0; ii < 11; ii++)
		{
			if (gteams[teamSel].ManMarking3[ii] != 255)
			{
				errorTot++;
				errorMsg << _T("Man marking is set up on preset 3; ");
				break;

			}
		}
		/*
		if (gteams[teamSel].AutoSub != 0)
		{
			errorTot++;
			errorMsg << _T("Auto subs are on; ");
		}
		if (gteams[teamSel].AutoOffside != 0)
		{
			errorTot++;
			errorMsg << _T("Auto offside trap is on; ");
		}
		if (gteams[teamSel].AutoPresetTactics != 0)
		{
			errorTot++;
			errorMsg << _T("Auto change preset tactics is on; ");
		}
		*/
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
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("It's all fucked."));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM)_T("Perfect, blaze."));
}
