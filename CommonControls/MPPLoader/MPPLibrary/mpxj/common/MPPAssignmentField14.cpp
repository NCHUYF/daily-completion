#pragma once
#include "stdafx.h"
#include "MPPAssignmentField14.h"


/**
* Retrieve an instance of the AssignmentField class based on the data read from an
* MS Project file.
*
* @param value value from an MS Project file
* @return AssignmentField instance
*/
AssignmentField MPPAssignmentField14::getInstance(int value)
{
	init();

    AssignmentField result = AF_START;

	if (value >= 0 && value < MAX_VALUE)
    {
        result = FIELD_ARRAY[value];
    }
    else
    {
        if ((value & 0x8000) != 0)
        {
			int baseValue = AssignmentField::AF_ENTERPRISE_CUSTOM_FIELD1;
			int id = baseValue + (value & 0xFFF);
			result = (AssignmentField)id;
        }
    }

    return (result);
}

/**
* Retrieve the ID of a field, as used by MS Project.
* 
* @param value field instance
* @return field ID
*/
int MPPAssignmentField14::getID(AssignmentField value)
{
	init();
    return (ID_ARRAY[(int)value]);
}

void MPPAssignmentField14::init()
{
	if (FIELD_ARRAY[0] != -1) return;

    FIELD_ARRAY[28] = AssignmentField::AF_ACTUAL_COST;
    FIELD_ARRAY[23] = AssignmentField::AF_ACTUAL_FINISH;
    FIELD_ARRAY[30] = AssignmentField::AF_ACTUAL_OVERTIME_COST;
    FIELD_ARRAY[13] = AssignmentField::AF_ACTUAL_OVERTIME_WORK;
    FIELD_ARRAY[631] = AssignmentField::AF_ACTUAL_OVERTIME_WORK_PROTECTED;
    FIELD_ARRAY[22] = AssignmentField::AF_ACTUAL_START;
    FIELD_ARRAY[10] = AssignmentField::AF_ACTUAL_WORK;
    FIELD_ARRAY[630] = AssignmentField::AF_ACTUAL_WORK_PROTECTED;
    FIELD_ARRAY[36] = AssignmentField::AF_ACWP;
    FIELD_ARRAY[636] = AssignmentField::AF_GUID;
    FIELD_ARRAY[638] = AssignmentField::AF_ASSIGNMENT_RESOURCE_GUID;
    FIELD_ARRAY[637] = AssignmentField::AF_ASSIGNMENT_TASK_GUID;
    FIELD_ARRAY[7] = AssignmentField::AF_ASSIGNMENT_UNITS;
    FIELD_ARRAY[714] = AssignmentField::AF_BASELINE10_BUDGET_COST;
    FIELD_ARRAY[713] = AssignmentField::AF_BASELINE10_BUDGET_WORK;
    FIELD_ARRAY[371] = AssignmentField::AF_BASELINE10_COST;
    FIELD_ARRAY[377] = AssignmentField::AF_BASELINE10_FINISH;
    FIELD_ARRAY[376] = AssignmentField::AF_BASELINE10_START;
    FIELD_ARRAY[370] = AssignmentField::AF_BASELINE10_WORK;
    FIELD_ARRAY[678] = AssignmentField::AF_BASELINE1_BUDGET_COST;
    FIELD_ARRAY[677] = AssignmentField::AF_BASELINE1_BUDGET_WORK;
    FIELD_ARRAY[290] = AssignmentField::AF_BASELINE1_COST;
    FIELD_ARRAY[296] = AssignmentField::AF_BASELINE1_FINISH;
    FIELD_ARRAY[295] = AssignmentField::AF_BASELINE1_START;
    FIELD_ARRAY[289] = AssignmentField::AF_BASELINE1_WORK;
    FIELD_ARRAY[682] = AssignmentField::AF_BASELINE2_BUDGET_COST;
    FIELD_ARRAY[681] = AssignmentField::AF_BASELINE2_BUDGET_WORK;
    FIELD_ARRAY[299] = AssignmentField::AF_BASELINE2_COST;
    FIELD_ARRAY[305] = AssignmentField::AF_BASELINE2_FINISH;
    FIELD_ARRAY[304] = AssignmentField::AF_BASELINE2_START;
    FIELD_ARRAY[298] = AssignmentField::AF_BASELINE2_WORK;
    FIELD_ARRAY[686] = AssignmentField::AF_BASELINE3_BUDGET_COST;
    FIELD_ARRAY[685] = AssignmentField::AF_BASELINE3_BUDGET_WORK;
    FIELD_ARRAY[308] = AssignmentField::AF_BASELINE3_COST;
    FIELD_ARRAY[314] = AssignmentField::AF_BASELINE3_FINISH;
    FIELD_ARRAY[313] = AssignmentField::AF_BASELINE3_START;
    FIELD_ARRAY[307] = AssignmentField::AF_BASELINE3_WORK;
    FIELD_ARRAY[690] = AssignmentField::AF_BASELINE4_BUDGET_COST;
    FIELD_ARRAY[689] = AssignmentField::AF_BASELINE4_BUDGET_WORK;
    FIELD_ARRAY[317] = AssignmentField::AF_BASELINE4_COST;
    FIELD_ARRAY[323] = AssignmentField::AF_BASELINE4_FINISH;
    FIELD_ARRAY[322] = AssignmentField::AF_BASELINE4_START;
    FIELD_ARRAY[316] = AssignmentField::AF_BASELINE4_WORK;
    FIELD_ARRAY[694] = AssignmentField::AF_BASELINE5_BUDGET_COST;
    FIELD_ARRAY[693] = AssignmentField::AF_BASELINE5_BUDGET_WORK;
    FIELD_ARRAY[326] = AssignmentField::AF_BASELINE5_COST;
    FIELD_ARRAY[332] = AssignmentField::AF_BASELINE5_FINISH;
    FIELD_ARRAY[331] = AssignmentField::AF_BASELINE5_START;
    FIELD_ARRAY[325] = AssignmentField::AF_BASELINE5_WORK;
    FIELD_ARRAY[698] = AssignmentField::AF_BASELINE6_BUDGET_COST;
    FIELD_ARRAY[697] = AssignmentField::AF_BASELINE6_BUDGET_WORK;
    FIELD_ARRAY[335] = AssignmentField::AF_BASELINE6_COST;
    FIELD_ARRAY[341] = AssignmentField::AF_BASELINE6_FINISH;
    FIELD_ARRAY[340] = AssignmentField::AF_BASELINE6_START;
    FIELD_ARRAY[334] = AssignmentField::AF_BASELINE6_WORK;
    FIELD_ARRAY[702] = AssignmentField::AF_BASELINE7_BUDGET_COST;
    FIELD_ARRAY[701] = AssignmentField::AF_BASELINE7_BUDGET_WORK;
    FIELD_ARRAY[344] = AssignmentField::AF_BASELINE7_COST;
    FIELD_ARRAY[350] = AssignmentField::AF_BASELINE7_FINISH;
    FIELD_ARRAY[349] = AssignmentField::AF_BASELINE7_START;
    FIELD_ARRAY[343] = AssignmentField::AF_BASELINE7_WORK;
    FIELD_ARRAY[706] = AssignmentField::AF_BASELINE8_BUDGET_COST;
    FIELD_ARRAY[705] = AssignmentField::AF_BASELINE8_BUDGET_WORK;
    FIELD_ARRAY[353] = AssignmentField::AF_BASELINE8_COST;
    FIELD_ARRAY[359] = AssignmentField::AF_BASELINE8_FINISH;
    FIELD_ARRAY[358] = AssignmentField::AF_BASELINE8_START;
    FIELD_ARRAY[352] = AssignmentField::AF_BASELINE8_WORK;
    FIELD_ARRAY[710] = AssignmentField::AF_BASELINE9_BUDGET_COST;
    FIELD_ARRAY[709] = AssignmentField::AF_BASELINE9_BUDGET_WORK;
    FIELD_ARRAY[362] = AssignmentField::AF_BASELINE9_COST;
    FIELD_ARRAY[368] = AssignmentField::AF_BASELINE9_FINISH;
    FIELD_ARRAY[367] = AssignmentField::AF_BASELINE9_START;
    FIELD_ARRAY[361] = AssignmentField::AF_BASELINE9_WORK;
    FIELD_ARRAY[674] = AssignmentField::AF_BASELINE_BUDGET_COST;
    FIELD_ARRAY[673] = AssignmentField::AF_BASELINE_BUDGET_WORK;
    FIELD_ARRAY[32] = AssignmentField::AF_BASELINE_COST;
    FIELD_ARRAY[147] = AssignmentField::AF_BASELINE_FINISH;
    FIELD_ARRAY[146] = AssignmentField::AF_BASELINE_START;
    FIELD_ARRAY[16] = AssignmentField::AF_BASELINE_WORK;
    FIELD_ARRAY[35] = AssignmentField::AF_BCWP;
    FIELD_ARRAY[34] = AssignmentField::AF_BCWS;
    FIELD_ARRAY[670] = AssignmentField::AF_BUDGET_COST;
    FIELD_ARRAY[669] = AssignmentField::AF_BUDGET_WORK;
    FIELD_ARRAY[72] = AssignmentField::AF_CONFIRMED;
    FIELD_ARRAY[26] = AssignmentField::AF_COST;
    FIELD_ARRAY[119] = AssignmentField::AF_COST1;
    FIELD_ARRAY[120] = AssignmentField::AF_COST2;
    FIELD_ARRAY[121] = AssignmentField::AF_COST3;
    FIELD_ARRAY[159] = AssignmentField::AF_COST4;
    FIELD_ARRAY[160] = AssignmentField::AF_COST5;
    FIELD_ARRAY[161] = AssignmentField::AF_COST6;
    FIELD_ARRAY[162] = AssignmentField::AF_COST7;
    FIELD_ARRAY[163] = AssignmentField::AF_COST8;
    FIELD_ARRAY[164] = AssignmentField::AF_COST9;
    FIELD_ARRAY[165] = AssignmentField::AF_COST10;
    FIELD_ARRAY[80] = AssignmentField::AF_COST_RATE_TABLE;
    FIELD_ARRAY[38] = AssignmentField::AF_COST_VARIANCE;
    FIELD_ARRAY[634] = AssignmentField::AF_CREATED;
    FIELD_ARRAY[247] = AssignmentField::AF_CV;
    FIELD_ARRAY[166] = AssignmentField::AF_DATE1;
    FIELD_ARRAY[175] = AssignmentField::AF_DATE10;
    FIELD_ARRAY[167] = AssignmentField::AF_DATE2;
    FIELD_ARRAY[168] = AssignmentField::AF_DATE3;
    FIELD_ARRAY[169] = AssignmentField::AF_DATE4;
    FIELD_ARRAY[170] = AssignmentField::AF_DATE5;
    FIELD_ARRAY[171] = AssignmentField::AF_DATE6;
    FIELD_ARRAY[172] = AssignmentField::AF_DATE7;
    FIELD_ARRAY[173] = AssignmentField::AF_DATE8;
    FIELD_ARRAY[174] = AssignmentField::AF_DATE9;
    FIELD_ARRAY[113] = AssignmentField::AF_DURATION1;
    FIELD_ARRAY[182] = AssignmentField::AF_DURATION10;
    FIELD_ARRAY[114] = AssignmentField::AF_DURATION2;
    FIELD_ARRAY[115] = AssignmentField::AF_DURATION3;
    FIELD_ARRAY[176] = AssignmentField::AF_DURATION4;
    FIELD_ARRAY[177] = AssignmentField::AF_DURATION5;
    FIELD_ARRAY[178] = AssignmentField::AF_DURATION6;
    FIELD_ARRAY[179] = AssignmentField::AF_DURATION7;
    FIELD_ARRAY[180] = AssignmentField::AF_DURATION8;
    FIELD_ARRAY[181] = AssignmentField::AF_DURATION9;
    FIELD_ARRAY[381] = AssignmentField::AF_ENTERPRISE_COST1;
    FIELD_ARRAY[390] = AssignmentField::AF_ENTERPRISE_COST10;
    FIELD_ARRAY[382] = AssignmentField::AF_ENTERPRISE_COST2;
    FIELD_ARRAY[383] = AssignmentField::AF_ENTERPRISE_COST3;
    FIELD_ARRAY[384] = AssignmentField::AF_ENTERPRISE_COST4;
    FIELD_ARRAY[385] = AssignmentField::AF_ENTERPRISE_COST5;
    FIELD_ARRAY[386] = AssignmentField::AF_ENTERPRISE_COST6;
    FIELD_ARRAY[387] = AssignmentField::AF_ENTERPRISE_COST7;
    FIELD_ARRAY[388] = AssignmentField::AF_ENTERPRISE_COST8;
    FIELD_ARRAY[389] = AssignmentField::AF_ENTERPRISE_COST9;
    FIELD_ARRAY[391] = AssignmentField::AF_ENTERPRISE_DATE1;
    FIELD_ARRAY[400] = AssignmentField::AF_ENTERPRISE_DATE10;
    FIELD_ARRAY[401] = AssignmentField::AF_ENTERPRISE_DATE11;
    FIELD_ARRAY[402] = AssignmentField::AF_ENTERPRISE_DATE12;
    FIELD_ARRAY[403] = AssignmentField::AF_ENTERPRISE_DATE13;
    FIELD_ARRAY[404] = AssignmentField::AF_ENTERPRISE_DATE14;
    FIELD_ARRAY[405] = AssignmentField::AF_ENTERPRISE_DATE15;
    FIELD_ARRAY[406] = AssignmentField::AF_ENTERPRISE_DATE16;
    FIELD_ARRAY[407] = AssignmentField::AF_ENTERPRISE_DATE17;
    FIELD_ARRAY[408] = AssignmentField::AF_ENTERPRISE_DATE18;
    FIELD_ARRAY[409] = AssignmentField::AF_ENTERPRISE_DATE19;
    FIELD_ARRAY[392] = AssignmentField::AF_ENTERPRISE_DATE2;
    FIELD_ARRAY[410] = AssignmentField::AF_ENTERPRISE_DATE20;
    FIELD_ARRAY[411] = AssignmentField::AF_ENTERPRISE_DATE21;
    FIELD_ARRAY[412] = AssignmentField::AF_ENTERPRISE_DATE22;
    FIELD_ARRAY[413] = AssignmentField::AF_ENTERPRISE_DATE23;
    FIELD_ARRAY[414] = AssignmentField::AF_ENTERPRISE_DATE24;
    FIELD_ARRAY[415] = AssignmentField::AF_ENTERPRISE_DATE25;
    FIELD_ARRAY[416] = AssignmentField::AF_ENTERPRISE_DATE26;
    FIELD_ARRAY[417] = AssignmentField::AF_ENTERPRISE_DATE27;
    FIELD_ARRAY[418] = AssignmentField::AF_ENTERPRISE_DATE28;
    FIELD_ARRAY[419] = AssignmentField::AF_ENTERPRISE_DATE29;
    FIELD_ARRAY[393] = AssignmentField::AF_ENTERPRISE_DATE3;
    FIELD_ARRAY[420] = AssignmentField::AF_ENTERPRISE_DATE30;
    FIELD_ARRAY[394] = AssignmentField::AF_ENTERPRISE_DATE4;
    FIELD_ARRAY[395] = AssignmentField::AF_ENTERPRISE_DATE5;
    FIELD_ARRAY[396] = AssignmentField::AF_ENTERPRISE_DATE6;
    FIELD_ARRAY[397] = AssignmentField::AF_ENTERPRISE_DATE7;
    FIELD_ARRAY[398] = AssignmentField::AF_ENTERPRISE_DATE8;
    FIELD_ARRAY[399] = AssignmentField::AF_ENTERPRISE_DATE9;
    FIELD_ARRAY[421] = AssignmentField::AF_ENTERPRISE_DURATION1;
    FIELD_ARRAY[430] = AssignmentField::AF_ENTERPRISE_DURATION10;
    FIELD_ARRAY[422] = AssignmentField::AF_ENTERPRISE_DURATION2;
    FIELD_ARRAY[423] = AssignmentField::AF_ENTERPRISE_DURATION3;
    FIELD_ARRAY[424] = AssignmentField::AF_ENTERPRISE_DURATION4;
    FIELD_ARRAY[425] = AssignmentField::AF_ENTERPRISE_DURATION5;
    FIELD_ARRAY[426] = AssignmentField::AF_ENTERPRISE_DURATION6;
    FIELD_ARRAY[427] = AssignmentField::AF_ENTERPRISE_DURATION7;
    FIELD_ARRAY[428] = AssignmentField::AF_ENTERPRISE_DURATION8;
    FIELD_ARRAY[429] = AssignmentField::AF_ENTERPRISE_DURATION9;
    FIELD_ARRAY[441] = AssignmentField::AF_ENTERPRISE_FLAG1;
    FIELD_ARRAY[450] = AssignmentField::AF_ENTERPRISE_FLAG10;
    FIELD_ARRAY[451] = AssignmentField::AF_ENTERPRISE_FLAG11;
    FIELD_ARRAY[452] = AssignmentField::AF_ENTERPRISE_FLAG12;
    FIELD_ARRAY[453] = AssignmentField::AF_ENTERPRISE_FLAG13;
    FIELD_ARRAY[454] = AssignmentField::AF_ENTERPRISE_FLAG14;
    FIELD_ARRAY[455] = AssignmentField::AF_ENTERPRISE_FLAG15;
    FIELD_ARRAY[456] = AssignmentField::AF_ENTERPRISE_FLAG16;
    FIELD_ARRAY[457] = AssignmentField::AF_ENTERPRISE_FLAG17;
    FIELD_ARRAY[458] = AssignmentField::AF_ENTERPRISE_FLAG18;
    FIELD_ARRAY[459] = AssignmentField::AF_ENTERPRISE_FLAG19;
    FIELD_ARRAY[442] = AssignmentField::AF_ENTERPRISE_FLAG2;
    FIELD_ARRAY[460] = AssignmentField::AF_ENTERPRISE_FLAG20;
    FIELD_ARRAY[443] = AssignmentField::AF_ENTERPRISE_FLAG3;
    FIELD_ARRAY[444] = AssignmentField::AF_ENTERPRISE_FLAG4;
    FIELD_ARRAY[445] = AssignmentField::AF_ENTERPRISE_FLAG5;
    FIELD_ARRAY[446] = AssignmentField::AF_ENTERPRISE_FLAG6;
    FIELD_ARRAY[447] = AssignmentField::AF_ENTERPRISE_FLAG7;
    FIELD_ARRAY[448] = AssignmentField::AF_ENTERPRISE_FLAG8;
    FIELD_ARRAY[449] = AssignmentField::AF_ENTERPRISE_FLAG9;
    FIELD_ARRAY[461] = AssignmentField::AF_ENTERPRISE_NUMBER1;
    FIELD_ARRAY[470] = AssignmentField::AF_ENTERPRISE_NUMBER10;
    FIELD_ARRAY[471] = AssignmentField::AF_ENTERPRISE_NUMBER11;
    FIELD_ARRAY[472] = AssignmentField::AF_ENTERPRISE_NUMBER12;
    FIELD_ARRAY[473] = AssignmentField::AF_ENTERPRISE_NUMBER13;
    FIELD_ARRAY[474] = AssignmentField::AF_ENTERPRISE_NUMBER14;
    FIELD_ARRAY[475] = AssignmentField::AF_ENTERPRISE_NUMBER15;
    FIELD_ARRAY[476] = AssignmentField::AF_ENTERPRISE_NUMBER16;
    FIELD_ARRAY[477] = AssignmentField::AF_ENTERPRISE_NUMBER17;
    FIELD_ARRAY[478] = AssignmentField::AF_ENTERPRISE_NUMBER18;
    FIELD_ARRAY[479] = AssignmentField::AF_ENTERPRISE_NUMBER19;
    FIELD_ARRAY[462] = AssignmentField::AF_ENTERPRISE_NUMBER2;
    FIELD_ARRAY[480] = AssignmentField::AF_ENTERPRISE_NUMBER20;
    FIELD_ARRAY[481] = AssignmentField::AF_ENTERPRISE_NUMBER21;
    FIELD_ARRAY[482] = AssignmentField::AF_ENTERPRISE_NUMBER22;
    FIELD_ARRAY[483] = AssignmentField::AF_ENTERPRISE_NUMBER23;
    FIELD_ARRAY[484] = AssignmentField::AF_ENTERPRISE_NUMBER24;
    FIELD_ARRAY[485] = AssignmentField::AF_ENTERPRISE_NUMBER25;
    FIELD_ARRAY[486] = AssignmentField::AF_ENTERPRISE_NUMBER26;
    FIELD_ARRAY[487] = AssignmentField::AF_ENTERPRISE_NUMBER27;
    FIELD_ARRAY[488] = AssignmentField::AF_ENTERPRISE_NUMBER28;
    FIELD_ARRAY[489] = AssignmentField::AF_ENTERPRISE_NUMBER29;
    FIELD_ARRAY[463] = AssignmentField::AF_ENTERPRISE_NUMBER3;
    FIELD_ARRAY[490] = AssignmentField::AF_ENTERPRISE_NUMBER30;
    FIELD_ARRAY[491] = AssignmentField::AF_ENTERPRISE_NUMBER31;
    FIELD_ARRAY[492] = AssignmentField::AF_ENTERPRISE_NUMBER32;
    FIELD_ARRAY[493] = AssignmentField::AF_ENTERPRISE_NUMBER33;
    FIELD_ARRAY[494] = AssignmentField::AF_ENTERPRISE_NUMBER34;
    FIELD_ARRAY[495] = AssignmentField::AF_ENTERPRISE_NUMBER35;
    FIELD_ARRAY[496] = AssignmentField::AF_ENTERPRISE_NUMBER36;
    FIELD_ARRAY[497] = AssignmentField::AF_ENTERPRISE_NUMBER37;
    FIELD_ARRAY[498] = AssignmentField::AF_ENTERPRISE_NUMBER38;
    FIELD_ARRAY[499] = AssignmentField::AF_ENTERPRISE_NUMBER39;
    FIELD_ARRAY[464] = AssignmentField::AF_ENTERPRISE_NUMBER4;
    FIELD_ARRAY[500] = AssignmentField::AF_ENTERPRISE_NUMBER40;
    FIELD_ARRAY[465] = AssignmentField::AF_ENTERPRISE_NUMBER5;
    FIELD_ARRAY[466] = AssignmentField::AF_ENTERPRISE_NUMBER6;
    FIELD_ARRAY[467] = AssignmentField::AF_ENTERPRISE_NUMBER7;
    FIELD_ARRAY[468] = AssignmentField::AF_ENTERPRISE_NUMBER8;
    FIELD_ARRAY[469] = AssignmentField::AF_ENTERPRISE_NUMBER9;
    FIELD_ARRAY[610] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE20;
    FIELD_ARRAY[612] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE21;
    FIELD_ARRAY[614] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE22;
    FIELD_ARRAY[616] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE23;
    FIELD_ARRAY[618] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE24;
    FIELD_ARRAY[620] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE25;
    FIELD_ARRAY[622] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE26;
    FIELD_ARRAY[624] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE27;
    FIELD_ARRAY[626] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE28;
    FIELD_ARRAY[628] = AssignmentField::AF_ENTERPRISE_RESOURCE_MULTI_VALUE29;
    FIELD_ARRAY[545] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE1;
    FIELD_ARRAY[554] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE10;
    FIELD_ARRAY[555] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE11;
    FIELD_ARRAY[556] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE12;
    FIELD_ARRAY[557] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE13;
    FIELD_ARRAY[558] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE14;
    FIELD_ARRAY[559] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE15;
    FIELD_ARRAY[560] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE16;
    FIELD_ARRAY[561] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE17;
    FIELD_ARRAY[562] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE18;
    FIELD_ARRAY[563] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE19;
    FIELD_ARRAY[546] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE2;
    FIELD_ARRAY[564] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE20;
    FIELD_ARRAY[565] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE21;
    FIELD_ARRAY[566] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE22;
    FIELD_ARRAY[567] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE23;
    FIELD_ARRAY[568] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE24;
    FIELD_ARRAY[569] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE25;
    FIELD_ARRAY[570] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE26;
    FIELD_ARRAY[571] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE27;
    FIELD_ARRAY[572] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE28;
    FIELD_ARRAY[573] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE29;
    FIELD_ARRAY[547] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE3;
    FIELD_ARRAY[548] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE4;
    FIELD_ARRAY[549] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE5;
    FIELD_ARRAY[550] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE6;
    FIELD_ARRAY[551] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE7;
    FIELD_ARRAY[552] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE8;
    FIELD_ARRAY[553] = AssignmentField::AF_ENTERPRISE_RESOURCE_OUTLINE_CODE9;
    FIELD_ARRAY[574] = AssignmentField::AF_ENTERPRISE_RESOURCE_RBS;
    FIELD_ARRAY[607] = AssignmentField::AF_ENTERPRISE_TEAM_MEMBER;
    FIELD_ARRAY[501] = AssignmentField::AF_ENTERPRISE_TEXT1;
    FIELD_ARRAY[510] = AssignmentField::AF_ENTERPRISE_TEXT10;
    FIELD_ARRAY[511] = AssignmentField::AF_ENTERPRISE_TEXT11;
    FIELD_ARRAY[512] = AssignmentField::AF_ENTERPRISE_TEXT12;
    FIELD_ARRAY[513] = AssignmentField::AF_ENTERPRISE_TEXT13;
    FIELD_ARRAY[514] = AssignmentField::AF_ENTERPRISE_TEXT14;
    FIELD_ARRAY[515] = AssignmentField::AF_ENTERPRISE_TEXT15;
    FIELD_ARRAY[516] = AssignmentField::AF_ENTERPRISE_TEXT16;
    FIELD_ARRAY[517] = AssignmentField::AF_ENTERPRISE_TEXT17;
    FIELD_ARRAY[518] = AssignmentField::AF_ENTERPRISE_TEXT18;
    FIELD_ARRAY[519] = AssignmentField::AF_ENTERPRISE_TEXT19;
    FIELD_ARRAY[502] = AssignmentField::AF_ENTERPRISE_TEXT2;
    FIELD_ARRAY[520] = AssignmentField::AF_ENTERPRISE_TEXT20;
    FIELD_ARRAY[521] = AssignmentField::AF_ENTERPRISE_TEXT21;
    FIELD_ARRAY[522] = AssignmentField::AF_ENTERPRISE_TEXT22;
    FIELD_ARRAY[523] = AssignmentField::AF_ENTERPRISE_TEXT23;
    FIELD_ARRAY[524] = AssignmentField::AF_ENTERPRISE_TEXT24;
    FIELD_ARRAY[525] = AssignmentField::AF_ENTERPRISE_TEXT25;
    FIELD_ARRAY[526] = AssignmentField::AF_ENTERPRISE_TEXT26;
    FIELD_ARRAY[527] = AssignmentField::AF_ENTERPRISE_TEXT27;
    FIELD_ARRAY[528] = AssignmentField::AF_ENTERPRISE_TEXT28;
    FIELD_ARRAY[529] = AssignmentField::AF_ENTERPRISE_TEXT29;
    FIELD_ARRAY[503] = AssignmentField::AF_ENTERPRISE_TEXT3;
    FIELD_ARRAY[530] = AssignmentField::AF_ENTERPRISE_TEXT30;
    FIELD_ARRAY[531] = AssignmentField::AF_ENTERPRISE_TEXT31;
    FIELD_ARRAY[532] = AssignmentField::AF_ENTERPRISE_TEXT32;
    FIELD_ARRAY[533] = AssignmentField::AF_ENTERPRISE_TEXT33;
    FIELD_ARRAY[534] = AssignmentField::AF_ENTERPRISE_TEXT34;
    FIELD_ARRAY[535] = AssignmentField::AF_ENTERPRISE_TEXT35;
    FIELD_ARRAY[536] = AssignmentField::AF_ENTERPRISE_TEXT36;
    FIELD_ARRAY[537] = AssignmentField::AF_ENTERPRISE_TEXT37;
    FIELD_ARRAY[538] = AssignmentField::AF_ENTERPRISE_TEXT38;
    FIELD_ARRAY[539] = AssignmentField::AF_ENTERPRISE_TEXT39;
    FIELD_ARRAY[504] = AssignmentField::AF_ENTERPRISE_TEXT4;
    FIELD_ARRAY[540] = AssignmentField::AF_ENTERPRISE_TEXT40;
    FIELD_ARRAY[505] = AssignmentField::AF_ENTERPRISE_TEXT5;
    FIELD_ARRAY[506] = AssignmentField::AF_ENTERPRISE_TEXT6;
    FIELD_ARRAY[507] = AssignmentField::AF_ENTERPRISE_TEXT7;
    FIELD_ARRAY[508] = AssignmentField::AF_ENTERPRISE_TEXT8;
    FIELD_ARRAY[509] = AssignmentField::AF_ENTERPRISE_TEXT9;
	FIELD_ARRAY[21] = AssignmentField::AF_FINISH;
    FIELD_ARRAY[103] = AssignmentField::AF_FINISH1;
    FIELD_ARRAY[187] = AssignmentField::AF_FINISH10;
    FIELD_ARRAY[104] = AssignmentField::AF_FINISH2;
    FIELD_ARRAY[105] = AssignmentField::AF_FINISH3;
    FIELD_ARRAY[106] = AssignmentField::AF_FINISH4;
    FIELD_ARRAY[107] = AssignmentField::AF_FINISH5;
    FIELD_ARRAY[183] = AssignmentField::AF_FINISH6;
    FIELD_ARRAY[184] = AssignmentField::AF_FINISH7;
    FIELD_ARRAY[185] = AssignmentField::AF_FINISH8;
    FIELD_ARRAY[186] = AssignmentField::AF_FINISH9;
    FIELD_ARRAY[263] = AssignmentField::AF_FINISH_VARIANCE;
    FIELD_ARRAY[275] = AssignmentField::AF_FIXED_MATERIAL_ASSIGNMENT;
    FIELD_ARRAY[123] = AssignmentField::AF_FLAG1;
    FIELD_ARRAY[122] = AssignmentField::AF_FLAG10;
    FIELD_ARRAY[188] = AssignmentField::AF_FLAG11;
    FIELD_ARRAY[189] = AssignmentField::AF_FLAG12;
    FIELD_ARRAY[190] = AssignmentField::AF_FLAG13;
    FIELD_ARRAY[191] = AssignmentField::AF_FLAG14;
    FIELD_ARRAY[192] = AssignmentField::AF_FLAG15;
    FIELD_ARRAY[193] = AssignmentField::AF_FLAG16;
    FIELD_ARRAY[194] = AssignmentField::AF_FLAG17;
    FIELD_ARRAY[195] = AssignmentField::AF_FLAG18;
    FIELD_ARRAY[196] = AssignmentField::AF_FLAG19;
    FIELD_ARRAY[124] = AssignmentField::AF_FLAG2;
    FIELD_ARRAY[197] = AssignmentField::AF_FLAG20;
    FIELD_ARRAY[125] = AssignmentField::AF_FLAG3;
    FIELD_ARRAY[126] = AssignmentField::AF_FLAG4;
    FIELD_ARRAY[127] = AssignmentField::AF_FLAG5;
    FIELD_ARRAY[128] = AssignmentField::AF_FLAG6;
    FIELD_ARRAY[129] = AssignmentField::AF_FLAG7;
    FIELD_ARRAY[130] = AssignmentField::AF_FLAG8;
    FIELD_ARRAY[131] = AssignmentField::AF_FLAG9;
    FIELD_ARRAY[150] = AssignmentField::AF_HYPERLINK_DATA;
    FIELD_ARRAY[152] = AssignmentField::AF_HYPERLINK;
    FIELD_ARRAY[153] = AssignmentField::AF_HYPERLINK_ADDRESS;
    FIELD_ARRAY[155] = AssignmentField::AF_HYPERLINK_HREF;
    FIELD_ARRAY[279] = AssignmentField::AF_HYPERLINK_SCREEN_TIP;
    FIELD_ARRAY[154] = AssignmentField::AF_HYPERLINK_SUBADDRESS;
    FIELD_ARRAY[246] = AssignmentField::AF_INDEX;
    FIELD_ARRAY[145] = AssignmentField::AF_LEVELING_DELAY;
    FIELD_ARRAY[132] = AssignmentField::AF_LINKED_FIELDS;
    FIELD_ARRAY[71] = AssignmentField::AF_NOTES;
    FIELD_ARRAY[108] = AssignmentField::AF_NUMBER1;
    FIELD_ARRAY[202] = AssignmentField::AF_NUMBER10;
    FIELD_ARRAY[203] = AssignmentField::AF_NUMBER11;
    FIELD_ARRAY[204] = AssignmentField::AF_NUMBER12;
    FIELD_ARRAY[205] = AssignmentField::AF_NUMBER13;
    FIELD_ARRAY[206] = AssignmentField::AF_NUMBER14;
    FIELD_ARRAY[207] = AssignmentField::AF_NUMBER15;
    FIELD_ARRAY[208] = AssignmentField::AF_NUMBER16;
    FIELD_ARRAY[209] = AssignmentField::AF_NUMBER17;
    FIELD_ARRAY[210] = AssignmentField::AF_NUMBER18;
    FIELD_ARRAY[211] = AssignmentField::AF_NUMBER19;
    FIELD_ARRAY[109] = AssignmentField::AF_NUMBER2;
    FIELD_ARRAY[212] = AssignmentField::AF_NUMBER20;
    FIELD_ARRAY[110] = AssignmentField::AF_NUMBER3;
    FIELD_ARRAY[111] = AssignmentField::AF_NUMBER4;
    FIELD_ARRAY[112] = AssignmentField::AF_NUMBER5;
    FIELD_ARRAY[198] = AssignmentField::AF_NUMBER6;
    FIELD_ARRAY[199] = AssignmentField::AF_NUMBER7;
    FIELD_ARRAY[200] = AssignmentField::AF_NUMBER8;
    FIELD_ARRAY[201] = AssignmentField::AF_NUMBER9;
    FIELD_ARRAY[135] = AssignmentField::AF_OVERALLOCATED;
    FIELD_ARRAY[27] = AssignmentField::AF_OVERTIME_COST;
    FIELD_ARRAY[9] = AssignmentField::AF_OVERTIME_WORK;
    FIELD_ARRAY[668] = AssignmentField::AF_OWNER;
    FIELD_ARRAY[19] = AssignmentField::AF_PEAK;
    FIELD_ARRAY[43] = AssignmentField::AF_PERCENT_WORK_COMPLETE;
    FIELD_ARRAY[44] = AssignmentField::AF_PROJECT;
    FIELD_ARRAY[11] = AssignmentField::AF_REGULAR_WORK;
    FIELD_ARRAY[29] = AssignmentField::AF_REMAINING_COST;
    FIELD_ARRAY[31] = AssignmentField::AF_REMAINING_OVERTIME_COST;
    FIELD_ARRAY[14] = AssignmentField::AF_REMAINING_OVERTIME_WORK;
    FIELD_ARRAY[12] = AssignmentField::AF_REMAINING_WORK;
    FIELD_ARRAY[4] = AssignmentField::AF_RESOURCE_ID;
    FIELD_ARRAY[6] = AssignmentField::AF_RESOURCE_NAME;
    FIELD_ARRAY[605] = AssignmentField::AF_RESOURCE_REQUEST_TYPE;
    FIELD_ARRAY[276] = AssignmentField::AF_RESOURCE_TYPE;
    FIELD_ARRAY[2] = AssignmentField::AF_RESOURCE_UNIQUE_ID;
    FIELD_ARRAY[73] = AssignmentField::AF_RESPONSE_PENDING;
    FIELD_ARRAY[20] = AssignmentField::AF_START;
    FIELD_ARRAY[98] = AssignmentField::AF_START1;
    FIELD_ARRAY[217] = AssignmentField::AF_START10;
    FIELD_ARRAY[99] = AssignmentField::AF_START2;
    FIELD_ARRAY[100] = AssignmentField::AF_START3;
    FIELD_ARRAY[101] = AssignmentField::AF_START4;
    FIELD_ARRAY[102] = AssignmentField::AF_START5;
    FIELD_ARRAY[213] = AssignmentField::AF_START6;
    FIELD_ARRAY[214] = AssignmentField::AF_START7;
    FIELD_ARRAY[215] = AssignmentField::AF_START8;
    FIELD_ARRAY[216] = AssignmentField::AF_START9;
    FIELD_ARRAY[262] = AssignmentField::AF_START_VARIANCE;
    FIELD_ARRAY[646] = AssignmentField::AF_SUMMARY;
    FIELD_ARRAY[37] = AssignmentField::AF_SV;
    FIELD_ARRAY[3] = AssignmentField::AF_TASK_ID;
    FIELD_ARRAY[5] = AssignmentField::AF_TASK_NAME;
    FIELD_ARRAY[379] = AssignmentField::AF_TASK_OUTLINE_NUMBER;
    FIELD_ARRAY[142] = AssignmentField::AF_TASK_SUMMARY_NAME;
    FIELD_ARRAY[1] = AssignmentField::AF_TASK_UNIQUE_ID;
    FIELD_ARRAY[75] = AssignmentField::AF_TEAM_STATUS_PENDING;
    FIELD_ARRAY[88] = AssignmentField::AF_TEXT1;
    FIELD_ARRAY[97] = AssignmentField::AF_TEXT10;
    FIELD_ARRAY[218] = AssignmentField::AF_TEXT11;
    FIELD_ARRAY[219] = AssignmentField::AF_TEXT12;
    FIELD_ARRAY[220] = AssignmentField::AF_TEXT13;
    FIELD_ARRAY[221] = AssignmentField::AF_TEXT14;
    FIELD_ARRAY[222] = AssignmentField::AF_TEXT15;
    FIELD_ARRAY[223] = AssignmentField::AF_TEXT16;
    FIELD_ARRAY[224] = AssignmentField::AF_TEXT17;
    FIELD_ARRAY[225] = AssignmentField::AF_TEXT18;
    FIELD_ARRAY[226] = AssignmentField::AF_TEXT19;
    FIELD_ARRAY[89] = AssignmentField::AF_TEXT2;
    FIELD_ARRAY[227] = AssignmentField::AF_TEXT20;
    FIELD_ARRAY[228] = AssignmentField::AF_TEXT21;
    FIELD_ARRAY[229] = AssignmentField::AF_TEXT22;
    FIELD_ARRAY[230] = AssignmentField::AF_TEXT23;
    FIELD_ARRAY[231] = AssignmentField::AF_TEXT24;
    FIELD_ARRAY[232] = AssignmentField::AF_TEXT25;
    FIELD_ARRAY[233] = AssignmentField::AF_TEXT26;
    FIELD_ARRAY[234] = AssignmentField::AF_TEXT27;
    FIELD_ARRAY[235] = AssignmentField::AF_TEXT28;
    FIELD_ARRAY[236] = AssignmentField::AF_TEXT29;
    FIELD_ARRAY[90] = AssignmentField::AF_TEXT3;
    FIELD_ARRAY[237] = AssignmentField::AF_TEXT30;
    FIELD_ARRAY[91] = AssignmentField::AF_TEXT4;
    FIELD_ARRAY[92] = AssignmentField::AF_TEXT5;
    FIELD_ARRAY[93] = AssignmentField::AF_TEXT6;
    FIELD_ARRAY[94] = AssignmentField::AF_TEXT7;
    FIELD_ARRAY[95] = AssignmentField::AF_TEXT8;
    FIELD_ARRAY[96] = AssignmentField::AF_TEXT9;
    FIELD_ARRAY[0] = AssignmentField::AF_UNIQUE_ID;
    FIELD_ARRAY[74] = AssignmentField::AF_UPDATE_NEEDED;
    FIELD_ARRAY[271] = AssignmentField::AF_VAC;
    FIELD_ARRAY[286] = AssignmentField::AF_WBS;
    FIELD_ARRAY[8] = AssignmentField::AF_WORK;
    FIELD_ARRAY[39] = AssignmentField::AF_WORK_CONTOUR;
    FIELD_ARRAY[248] = AssignmentField::AF_WORK_VARIANCE;
    FIELD_ARRAY[49] = AssignmentField::AF_TIMEPHASED_WORK;
    FIELD_ARRAY[50] = AssignmentField::AF_TIMEPHASED_ACTUAL_WORK;
    FIELD_ARRAY[51] = AssignmentField::AF_TIMEPHASED_ACTUAL_OVERTIME_WORK;
    FIELD_ARRAY[52] = AssignmentField::AF_TIMEPHASED_BASELINE_WORK;
    FIELD_ARRAY[53] = AssignmentField::AF_TIMEPHASED_BASELINE_COST;
    FIELD_ARRAY[291] = AssignmentField::AF_TIMEPHASED_BASELINE1_WORK;
    FIELD_ARRAY[292] = AssignmentField::AF_TIMEPHASED_BASELINE1_COST;
    FIELD_ARRAY[300] = AssignmentField::AF_TIMEPHASED_BASELINE2_WORK;
    FIELD_ARRAY[301] = AssignmentField::AF_TIMEPHASED_BASELINE2_COST;
    FIELD_ARRAY[309] = AssignmentField::AF_TIMEPHASED_BASELINE3_WORK;
    FIELD_ARRAY[310] = AssignmentField::AF_TIMEPHASED_BASELINE3_COST;
    FIELD_ARRAY[318] = AssignmentField::AF_TIMEPHASED_BASELINE4_WORK;
    FIELD_ARRAY[319] = AssignmentField::AF_TIMEPHASED_BASELINE4_COST;
    FIELD_ARRAY[327] = AssignmentField::AF_TIMEPHASED_BASELINE5_WORK;
    FIELD_ARRAY[328] = AssignmentField::AF_TIMEPHASED_BASELINE5_COST;
    FIELD_ARRAY[336] = AssignmentField::AF_TIMEPHASED_BASELINE6_WORK;
    FIELD_ARRAY[337] = AssignmentField::AF_TIMEPHASED_BASELINE6_COST;
    FIELD_ARRAY[345] = AssignmentField::AF_TIMEPHASED_BASELINE7_WORK;
    FIELD_ARRAY[346] = AssignmentField::AF_TIMEPHASED_BASELINE7_COST;
    FIELD_ARRAY[354] = AssignmentField::AF_TIMEPHASED_BASELINE8_WORK;
    FIELD_ARRAY[355] = AssignmentField::AF_TIMEPHASED_BASELINE8_COST;
    FIELD_ARRAY[363] = AssignmentField::AF_TIMEPHASED_BASELINE9_WORK;
    FIELD_ARRAY[364] = AssignmentField::AF_TIMEPHASED_BASELINE9_COST;
    FIELD_ARRAY[372] = AssignmentField::AF_TIMEPHASED_BASELINE10_WORK;
    FIELD_ARRAY[373] = AssignmentField::AF_TIMEPHASED_BASELINE10_COST;
    FIELD_ARRAY[270] = AssignmentField::AF_VARIABLE_RATE_UNITS;
    FIELD_ARRAY[55] = AssignmentField::AF_LEVELING_DELAY_UNITS;
    FIELD_ARRAY[116] = AssignmentField::AF_DURATION1_UNITS;
    FIELD_ARRAY[117] = AssignmentField::AF_DURATION2_UNITS;
    FIELD_ARRAY[118] = AssignmentField::AF_DURATION3_UNITS;
    FIELD_ARRAY[238] = AssignmentField::AF_DURATION4_UNITS;
    FIELD_ARRAY[239] = AssignmentField::AF_DURATION5_UNITS;
    FIELD_ARRAY[240] = AssignmentField::AF_DURATION6_UNITS;
    FIELD_ARRAY[241] = AssignmentField::AF_DURATION7_UNITS;
    FIELD_ARRAY[242] = AssignmentField::AF_DURATION8_UNITS;
    FIELD_ARRAY[243] = AssignmentField::AF_DURATION9_UNITS;
    FIELD_ARRAY[244] = AssignmentField::AF_DURATION10_UNITS;

	for (int loop = 0; loop < MAX_VALUE; loop++)
	{
		AssignmentField assignmentField = FIELD_ARRAY[loop];
		if (assignmentField != (AssignmentField)-1)
		{
			ID_ARRAY[(int) assignmentField] = loop;
		}
	}
}

AssignmentField MPPAssignmentField14::FIELD_ARRAY[MAX_VALUE] = { (AssignmentField)-1 };
int MPPAssignmentField14::ID_ARRAY[AssignmentField::AF_FINISH+1] = { -1 };