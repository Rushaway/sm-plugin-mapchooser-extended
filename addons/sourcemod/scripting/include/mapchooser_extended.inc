/**
 * vim: set ts=4 :
 * =============================================================================
 * MapChooser Extended
 * Creates a map vote at appropriate times, setting sm_nextmap to the winning
 * vote
 *
 * MapChooser Extended (C)2011-2013 Powerlord (Ross Bemrose)
 * SourceMod (C)2004-2007 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#if defined _mapchooser_extended_included_
  #endinput
#endif
#define _mapchooser_extended_included_
#include <mapchooser>

// MCE 1.9 series

enum CanNominateResult
{
	CanNominate_No_VoteFull,		/** No, nominations list is full */
	CanNominate_No_VoteInProgress,	/** No, map vote is in progress */
	CanNominate_No_VoteComplete,	/** No, map vote is completed */
	CanNominate_Yes,				/** Yes, you can nominate */
};


/**
 * Called whenever warning timer starts
 *
 */
forward void OnMapVoteWarningStart();

/**
 * Called whenever runoff warning timer starts
 */
forward void OnMapVoteRunnoffWarningStart();

/**
 * Called whenever the timer ticks
 */
forward void OnMapVoteWarningTick(int time);

/**
 * Called whenever vote starts
 *
 * @deprecated Will be removed in MapChooser 1.8.  Use OnMapVoteStarted instead.
 */
forward void OnMapVoteStart();

/**
 * Called whenever vote ends
 */
forward void OnMapVoteEnd(const char[] map);

/**
 * Called when a client who own a nomination disconnect
 */
forward void OnNominationDisconnect(char[] oldmap, int owner);

/**
 * Called when the nextmap is set
 */
forward void OnSetNextMap(const char[] map);

/** 
 * Is nomination was made by a client?
 * 
 * @param owner 	Client index
 * @param map 		buffer to store map name (PLATFORM_MAX_PATH)
 * @return 			true if nomination was made by client (and map is stored in buffer)
 */
native bool GetNominationByOwner(int owner, char[] map);

/**
 * Is a map on the current game's official list?
 * This should be treated as informative only.
 *
 * @param map 	Name of map to check
 * @return 		true if it's on the list of official maps for this game
 */
native bool IsMapOfficial(const char[] map);

/**
 * Is nominate allowed?
 *
 * @return		A CanNominateResult corresponding to whether a vote is allowed or not
 */
native CanNominateResult CanNominate();

/**
 * Add map to nomination exclude list.
 * Known as cooldown.
 *
 * @param map 		Name of map
 * @param cooldown 	Cooldown, interpretation depends on mode.
 * @param mode 		0: Normal, use cooldown value from config/default.
 *					1: Set or replace cooldown with cooldown value.
 *					2: Set or replace cooldown with cooldown value if greater than current cooldown.
 * @return 			true on success
 */
native bool ExcludeMap(const char[] map, int cooldown = 0, int mode = 0);
// Cooldown in seconds
native bool ExcludeMapTime(const char[] map, int cooldown = 0, int mode = 0);

native int GetMapCooldown(const char[] map);
native int GetMapCooldownTime(const char[] map); // in unix time
native int GetMapMinTime(const char[] map);
native int GetMapMaxTime(const char[] map);
native int GetMapMinPlayers(const char[] map);
native int GetMapMaxPlayers(const char[] map);

// 0 = Okay
// >0 = Minutes till Okay
native int GetMapTimeRestriction(const char[] map);

// <0 = Less than MinPlayers
// 0 = Okay
// >0 = More than MaxPlayers
native int GetMapPlayerRestriction(const char[] map);

// <=0 = No group
// >0 = Groups found
native int GetMapGroups(const char[] map, int[] groups, int size);

// <0 = No restriction
// >=0 = Group _max -> Group full
native int GetMapGroupRestriction(const char[] map, int client = 0);

native bool IsMapAdminRestricted(const char[] map);

native bool IsClientMapAdminRestricted(const char[] map, int client = 0);

native bool IsMapVIPRestricted(const char[] map);

native bool IsClientMapVIPRestricted(const char[] map, int client = 0);

native bool IsMapLeaderRestricted(const char[] map);

native bool IsClientMapLeaderRestricted(const char[] map, int client = 0);

/**
 * Amount of Extends left on the current map
 *
 * @return			amounts of extends left
*/
native int GetExtendsLeft();

native bool AreRestrictionsActive();

native int SimulateMapEnd();

public SharedPlugin __pl_mapchooser_extended =
{
	name = "mapchooser",
	file = "mapchooser_extended.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};