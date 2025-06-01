#include <string>
#include <sstream>
#include "editor.h"
#include "resource.h"
#include <list>
#include "aatf.h"
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
int goldCOM = 1;

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


void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players)
{
	player_entry player;
	tstring msgOut;
	msgOut+=_T("Team: ");
	msgOut+=gteams[teamSel].name;
	msgOut+=_T("\r\n");

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


int goldA = 2;
int silverA = 2;
int regA = 2;
int manletA = 3;

void aatf_single(HWND hAatfbox, int pesVersion, int teamSel, player_entry* gplayers, team_entry* gteams, int gnum_players, bool useSuggestions)
{
    player_entry player;
    std::list<player_entry> manlets_without_bonus;
    tstring msgOut;
    msgOut += _T("Team: ");
    msgOut += gteams[teamSel].name;
    msgOut += _T("\r\n");

    bool isManlet = false;
    bool usingPurple = true;

    numGK = 0;
    //Player ratings
    numReg = 0;
    numSilver = 0;
    numGold = 0;
    //Height brackets
    numColossal = 0;
    numGiant = 0;
    numTall = 0;
    numMid = 0;
    numManlet = 0;
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
		int heightMod = 0;
		int weakFootUse = 0;
		int weakFootAcc = 0;
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
        if(pesVersion>16) rating = max(player.phys_cont, rating); //Not in 16
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
		if(player.play_pos[requiredAPos] != 2)
		{
			errorTot++;
			errorMsg << _T("Doesn't have A in registered position; ");
		}
		
		//Count number of registered GKs
		if(player.reg_pos == 0) numGK++;

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
            numManlet++;
            cardMod++; //Manlets get a bonus card
            if (player.height < 175 && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Height can be increased to 175]; ");
            }
        }
        else if (player.height == heightMid)
            numMid++;
        else if (player.height == heightTall)
            numTall++;
        else if (player.height == heightTallGK && player.reg_pos == 0) //GK
            numTall++;
        else if (player.height == heightGiant)
            numGiant++;
        else if (player.height == heightColossal)
            numColossal++;
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
        if (rating < silverRate - silverGiantPen) //Regular player
        {
            numReg++;
            targetRate = regRate;
            targetRate2 = regRate;
            if (player.reg_pos == 0) //GK target rate is 77
            {
                targetRate = gkRate;
                targetRate2 = gkRate;
            }

			weakFootUse = regWeakFootUse;
			weakFootAcc = regWeakFootAcc;

            if (player.height > heightManlet)
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

            if (player.form + 1 != regForm)
            {
                errorTot++;
                errorMsg << _T("Form is ") << player.form + 1 << _T(", should be ") << regForm << _T("; ");
            }

            if (isManlet) {
                if (countA > manletA) {
                    cardMod -= (countA - manletA); //For VGL: trade A pos for a card
                }

                if (countA < manletA && player.play_pos[12] != 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << manletA << _T("]; ");
                }
            }
            else {
                if (countA > regA) {
                    cardMod -= (countA - regA); //For VGL: trade A pos for a card
                }

                if (countA < regA && player.play_pos[12] != 2 && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << regA << _T("]; ");
                }
            }

            if (player.reg_pos == 0) //GK gets 2 cards
            {
                cardMod += min(gkTrickCards, numTrick); //1 free tricks
                cardMod += min(gkCOM, numCom); //0 free COM styles
                cardLimit = gkSkillCards + cardMod;
                if (cardCount > cardLimit)
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

            if (rating == targetRate && player.height < heightManlet) { //If the player is a manlet and doesn't have the manlet bonus
                manlets_without_bonus.push_back(player);
            }

            if (rating != targetRate)
            {
                if (rating == targetRate + manletBonus && player.height <= heightManlet)
                {
                    usingPurple = true;
                    targetRate += manletBonus;
                    targetRate2 += manletBonus;
                }
                else
                {
                    errorTot++;
                    errorMsg << _T("Illegal Ability scores; ");
                }
            }

            if (player.injury + 1 != regIR)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << regIR << _T("; ");
            }
        }
        /* SILVER */
        else if (rating < goldRate - goldGiantPen) //Silver player
        {
            numSilver++;
            targetRate = silverRate;
            targetRate2 = silverRate;

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
            if (player.height == heightGiant) //HA get penalty
            {
                targetRate -= silverGiantPen;
                targetRate2 -= silverGiantPen;
            }
            else if (player.height <= heightManlet && rating == targetRate + silverManletBonus)
            {
                usingPurple = true;
                targetRate += silverManletBonus;
                targetRate2 += silverManletBonus;
            }
            if (isManlet) {
                if (countA > manletA) {
                    cardMod -= (countA - manletA); //For VGL: trade A pos for a card
                }

                if (countA < manletA && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << manletA << _T("]; ");
                }
            }
            else {
                if (countA > silverA) {
                    cardMod -= (countA - silverA); //For VGL: trade A pos for a card
                }

                if (countA < silverA && useSuggestions)
                {
                    suggestionTot++;
                    suggestionMsg << _T("[Has ") << countA << _T(" A position, can be ") << silverA << _T("]; ");
                }
            }
            cardMod += min(silverTrickCards, numTrick); //3 free tricks
            cardMod += min(silverCOM, numCom); //1 free COM
            //cardMod += min(1, (countA - 1)); //1 free A-position
            cardLimit = silverSkillCards + cardMod; //4 skill cards
            if (cardCount > cardLimit)
            {
                errorTot++;
                errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
            }

            if (numCom < silverCOM && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << numCom << _T(" COM, can be ") << silverCOM << _T("]; ");
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
            if (player.injury + 1 != silverIR)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << silverIR << _T("; ");
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

			if (player.height > heightGiant)
			{
				errorMsg << _T("Gold heights cannot exceed ") << heightGiant << _T("cm; ");
			}
			
            cardMod += min(goldTrickCards, numTrick); //4 free tricks
			cardMod += min(goldCOM, numCom); //2 free COMs
			cardLimit = goldSkillCards + cardMod; //5 skill cards
           
			if(player.injury+1 > goldIR)
			{
				errorTot++;
				errorMsg << _T("Injury resist is ") << player.injury+1 << _T(", should be ") << goldIR << _T("; ");
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
		if ( ((player.height - heightMod) <= heightManlet) )
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

            cardMod += min(goldTrickCards, numTrick); //4 free tricks
            cardMod += min(goldCOM, numCom); //2 free COMs
            cardLimit = goldSkillCards + cardMod; //5 skill cards
            if (cardCount > cardLimit)
            {
                errorTot++;
                errorMsg << _T("Has ") << cardCount << _T(" cards, only allowed ") << cardLimit << _T("; ");
            }

            if (numCom < goldCOM && useSuggestions)
            {
                suggestionTot++;
                suggestionMsg << _T("[Has ") << numCom << _T(" COM, can be ") << goldCOM << _T("]; ");
            }

		if (eCheck)
		{
			if (cardCount < min(cardLimit,10)) errorMsg << _T("WARN: Has ") << cardCount << _T(" cards, allowed ") << cardLimit << _T("; ");
			if (player.weak_use + 1 < weakFootUse) errorMsg << _T("WARN: Has weak usage") << player.weak_use + 1 << _T(", allowed ") << weakFootUse << _T("; ");
			if (player.weak_acc + 1 < weakFootAcc) errorMsg << _T("WARN: Has weak accuracy") << player.weak_acc + 1 << _T(", allowed ") << weakFootAcc << _T("; ");
		}

            if (rating != targetRate)
            {
                errorTot++;
                errorMsg << _T("Illegal Ability scores; ");
            }

            if (player.injury + 1 > goldIR)
            {
                errorTot++;
                errorMsg << _T("Injury resist is ") << player.injury + 1 << _T(", should be ") << goldIR << _T("; ");
            }
        }

		//Check individual skill ratings
		//								c_skillRate			s_skillName			n_minPesVersion	n_targetRate
		skillCheck skillChecks[25] = {	{player.drib,		_T("Dribbling"),			0,		targetRate	},
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

		if(errorMsg.rdbuf()->in_avail())
		{
			errorMsg << _T("\r\n");
			msgOut+=_T("\t");
			msgOut+=errorMsg.str();
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
    if (!usingPurple) //Using Blue height system
    {
        msgOut += _T("Using Blue height system\r\n");
        if (diff = blueColossal - numColossal)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numColossal << _T("/") << blueColossal << _T(" ") << heightColossal << _T("cm players; ");
        }
        if (diff = blueGiant - numGiant)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numGiant << _T("/") << blueGiant << _T(" ") << heightGiant << _T("cm players; ");
        }
        if (diff = blueTall - numTall)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numTall << _T("/") << blueTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
        }
        if (diff = blueMid - numMid)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numMid << _T("/") << blueMid << _T(" ") << heightMid << _T("cm players; ");
        }
        if (diff = blueManlet - numManlet)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numManlet << _T("/") << blueManlet << _T(" ") << heightManlet << _T("cm players; ");
        }
    }
    else //Using purple height system
    {
        msgOut += _T("Using Purple height system\r\n");
        if (diff = purpleColossal - numColossal)
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
            errorMsg << _T("Has ") << numColossal << _T("/") << purpleColossal << _T(" ") << heightColossal << _T("cm players; ");
        }
        if (diff = purpleGiant - numGiant)
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
            errorMsg << _T("Has ") << numGiant << _T("/") << purpleGiant << _T(" ") << heightGiant << _T("cm players; ");
        }
        if (diff = purpleTall - numTall)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numTall << _T("/") << purpleTall << _T(" ") << heightTall << _T("/") << heightTallGK << _T("cm players; ");
        }
        if (diff = purpleMid - numMid)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numMid << _T("/") << purpleMid << _T(" ") << heightMid << _T("cm players; ");
        }
        if (diff = purpleManlet - numManlet)
        {
            if (diff > 0)
            {
                errorTot += diff;
            }
            else
            {
                errorTot -= diff;
            }
            errorMsg << _T("Has ") << numManlet << _T("/") << purpleManlet << _T(" ") << heightManlet << _T("cm players; ");
        }
        std::list<player_entry>::iterator it;
        for (it = manlets_without_bonus.begin(); it != manlets_without_bonus.end(); ++it) {
            suggestionTot++;
            suggestionMsg << _T("[Player ") << it->name << _T(" is a manlet and can have ") << regRate + manletBonus << _T(" rating]; \r\n");
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
	if(errorTot)
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("KWABxport melty in the 'tor"));
	else
		SendDlgItemMessage(hAatfbox, IDB_AATFOK, WM_SETTEXT, 0, (LPARAM) _T("Well, Seymour, this export made it... despite your directions"));
}
