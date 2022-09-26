#include "stdafx.h"
#include "MPPResourceField14.h"

/**
* Retrieve an instance of the Resource2Field class based on the data read from an
* MS Project file.
*
* @param value value from an MS Project file
* @return Resource2Field instance
*/
bool MPPResource2Field14::getInstance(int value, Resource2Field& field)
{
	init();
    //Resource2Field result = RF_START;

	if (value >= 0 && value < MAX_VALUE)
	{
		field = FIELD_ARRAY[value];
	}
	else if ((value & 0x8000) != 0)
	{
		int baseValue = Resource2Field::RF_ENTERPRISE_CUSTOM_FIELD1;
		int id = baseValue + (value & 0xFFF);
		field = (Resource2Field)id;
	}
	else
		return false;
	return true;
}

/**
* Retrieve the ID of a field, as used by MS Project.
* 
* @param value field instance
* @return field ID
*/
int MPPResource2Field14::getID(Resource2Field value)
{
	init();
    return (ID_ARRAY[value]);
}

void MPPResource2Field14::init()
{
	if (FIELD_ARRAY[0] != -1) return;

    FIELD_ARRAY[29] = Resource2Field::RF_PERCENT_WORK_COMPLETE;
    FIELD_ARRAY[19] = Resource2Field::RF_ACCRUE_AT;
    FIELD_ARRAY[808] = Resource2Field::RF_ACTIVE;
    FIELD_ARRAY[11] = Resource2Field::RF_ACTUAL_COST;
    FIELD_ARRAY[271] = Resource2Field::RF_ACTUAL_FINISH;
    FIELD_ARRAY[48] = Resource2Field::RF_ACTUAL_OVERTIME_COST;
    FIELD_ARRAY[39] = Resource2Field::RF_ACTUAL_OVERTIME_WORK;
    FIELD_ARRAY[270] = Resource2Field::RF_ACTUAL_START;
    FIELD_ARRAY[14] = Resource2Field::RF_ACTUAL_WORK;
    FIELD_ARRAY[53] = Resource2Field::RF_ACWP;
    FIELD_ARRAY[144] = Resource2Field::RF_ASSIGNMENT;
    FIELD_ARRAY[257] = Resource2Field::RF_ASSIGNMENT_DELAY;
    FIELD_ARRAY[803] = Resource2Field::RF_ASSIGNMENT_OWNER;
    FIELD_ARRAY[258] = Resource2Field::RF_ASSIGNMENT_UNITS;
    FIELD_ARRAY[57] = Resource2Field::RF_AVAILABLE_FROM;
    FIELD_ARRAY[58] = Resource2Field::RF_AVAILABLE_TO;
    FIELD_ARRAY[5] = Resource2Field::RF_BASE_CALENDAR;
    FIELD_ARRAY[757] = Resource2Field::RF_BASELINE_BUDGET_COST;
    FIELD_ARRAY[756] = Resource2Field::RF_BASELINE_BUDGET_WORK;
    FIELD_ARRAY[17] = Resource2Field::RF_BASELINE_COST;
    FIELD_ARRAY[260] = Resource2Field::RF_BASELINE_FINISH;
    FIELD_ARRAY[259] = Resource2Field::RF_BASELINE_START;
    FIELD_ARRAY[15] = Resource2Field::RF_BASELINE_WORK;
    FIELD_ARRAY[761] = Resource2Field::RF_BASELINE1_BUDGET_COST;
    FIELD_ARRAY[760] = Resource2Field::RF_BASELINE1_BUDGET_WORK;
    FIELD_ARRAY[343] = Resource2Field::RF_BASELINE1_COST;
    FIELD_ARRAY[349] = Resource2Field::RF_BASELINE1_FINISH;
    FIELD_ARRAY[348] = Resource2Field::RF_BASELINE1_START;
    FIELD_ARRAY[342] = Resource2Field::RF_BASELINE1_WORK;
    FIELD_ARRAY[797] = Resource2Field::RF_BASELINE10_BUDGET_COST;
    FIELD_ARRAY[796] = Resource2Field::RF_BASELINE10_BUDGET_WORK;
    FIELD_ARRAY[433] = Resource2Field::RF_BASELINE10_COST;
    FIELD_ARRAY[439] = Resource2Field::RF_BASELINE10_FINISH;
    FIELD_ARRAY[438] = Resource2Field::RF_BASELINE10_START;
    FIELD_ARRAY[432] = Resource2Field::RF_BASELINE10_WORK;
    FIELD_ARRAY[765] = Resource2Field::RF_BASELINE2_BUDGET_COST;
    FIELD_ARRAY[764] = Resource2Field::RF_BASELINE2_BUDGET_WORK;
    FIELD_ARRAY[353] = Resource2Field::RF_BASELINE2_COST;
    FIELD_ARRAY[359] = Resource2Field::RF_BASELINE2_FINISH;
    FIELD_ARRAY[358] = Resource2Field::RF_BASELINE2_START;
    FIELD_ARRAY[352] = Resource2Field::RF_BASELINE2_WORK;
    FIELD_ARRAY[769] = Resource2Field::RF_BASELINE3_BUDGET_COST;
    FIELD_ARRAY[768] = Resource2Field::RF_BASELINE3_BUDGET_WORK;
    FIELD_ARRAY[363] = Resource2Field::RF_BASELINE3_COST;
    FIELD_ARRAY[369] = Resource2Field::RF_BASELINE3_FINISH;
    FIELD_ARRAY[368] = Resource2Field::RF_BASELINE3_START;
    FIELD_ARRAY[362] = Resource2Field::RF_BASELINE3_WORK;
    FIELD_ARRAY[773] = Resource2Field::RF_BASELINE4_BUDGET_COST;
    FIELD_ARRAY[772] = Resource2Field::RF_BASELINE4_BUDGET_WORK;
    FIELD_ARRAY[373] = Resource2Field::RF_BASELINE4_COST;
    FIELD_ARRAY[379] = Resource2Field::RF_BASELINE4_FINISH;
    FIELD_ARRAY[378] = Resource2Field::RF_BASELINE4_START;
    FIELD_ARRAY[372] = Resource2Field::RF_BASELINE4_WORK;
    FIELD_ARRAY[777] = Resource2Field::RF_BASELINE5_BUDGET_COST;
    FIELD_ARRAY[776] = Resource2Field::RF_BASELINE5_BUDGET_WORK;
    FIELD_ARRAY[383] = Resource2Field::RF_BASELINE5_COST;
    FIELD_ARRAY[389] = Resource2Field::RF_BASELINE5_FINISH;
    FIELD_ARRAY[388] = Resource2Field::RF_BASELINE5_START;
    FIELD_ARRAY[382] = Resource2Field::RF_BASELINE5_WORK;
    FIELD_ARRAY[781] = Resource2Field::RF_BASELINE6_BUDGET_COST;
    FIELD_ARRAY[780] = Resource2Field::RF_BASELINE6_BUDGET_WORK;
    FIELD_ARRAY[393] = Resource2Field::RF_BASELINE6_COST;
    FIELD_ARRAY[399] = Resource2Field::RF_BASELINE6_FINISH;
    FIELD_ARRAY[398] = Resource2Field::RF_BASELINE6_START;
    FIELD_ARRAY[392] = Resource2Field::RF_BASELINE6_WORK;
    FIELD_ARRAY[785] = Resource2Field::RF_BASELINE7_BUDGET_COST;
    FIELD_ARRAY[784] = Resource2Field::RF_BASELINE7_BUDGET_WORK;
    FIELD_ARRAY[403] = Resource2Field::RF_BASELINE7_COST;
    FIELD_ARRAY[409] = Resource2Field::RF_BASELINE7_FINISH;
    FIELD_ARRAY[408] = Resource2Field::RF_BASELINE7_START;
    FIELD_ARRAY[402] = Resource2Field::RF_BASELINE7_WORK;
    FIELD_ARRAY[789] = Resource2Field::RF_BASELINE8_BUDGET_COST;
    FIELD_ARRAY[788] = Resource2Field::RF_BASELINE8_BUDGET_WORK;
    FIELD_ARRAY[413] = Resource2Field::RF_BASELINE8_COST;
    FIELD_ARRAY[419] = Resource2Field::RF_BASELINE8_FINISH;
    FIELD_ARRAY[418] = Resource2Field::RF_BASELINE8_START;
    FIELD_ARRAY[412] = Resource2Field::RF_BASELINE8_WORK;
    FIELD_ARRAY[793] = Resource2Field::RF_BASELINE9_BUDGET_COST;
    FIELD_ARRAY[792] = Resource2Field::RF_BASELINE9_BUDGET_WORK;
    FIELD_ARRAY[423] = Resource2Field::RF_BASELINE9_COST;
    FIELD_ARRAY[429] = Resource2Field::RF_BASELINE9_FINISH;
    FIELD_ARRAY[428] = Resource2Field::RF_BASELINE9_START;
    FIELD_ARRAY[422] = Resource2Field::RF_BASELINE9_WORK;
    FIELD_ARRAY[52] = Resource2Field::RF_BCWP;
    FIELD_ARRAY[51] = Resource2Field::RF_BCWS;
    FIELD_ARRAY[699] = Resource2Field::RF_BOOKING_TYPE;
    FIELD_ARRAY[752] = Resource2Field::RF_BUDGET;
    FIELD_ARRAY[754] = Resource2Field::RF_BUDGET_COST;
    FIELD_ARRAY[753] = Resource2Field::RF_BUDGET_WORK;
    FIELD_ARRAY[729] = Resource2Field::RF_CALENDAR_GUID;
    FIELD_ARRAY[163] = Resource2Field::RF_CAN_LEVEL;
    FIELD_ARRAY[10] = Resource2Field::RF_CODE;
    FIELD_ARRAY[261] = Resource2Field::RF_CONFIRMED;
    FIELD_ARRAY[12] = Resource2Field::RF_COST;
    FIELD_ARRAY[801] = Resource2Field::RF_COST_CENTER;
    FIELD_ARRAY[18] = Resource2Field::RF_COST_PER_USE;
    FIELD_ARRAY[269] = Resource2Field::RF_COST_RATE_TABLE;
    FIELD_ARRAY[24] = Resource2Field::RF_COST_VARIANCE;
    FIELD_ARRAY[123] = Resource2Field::RF_COST1;
    FIELD_ARRAY[172] = Resource2Field::RF_COST10;
    FIELD_ARRAY[124] = Resource2Field::RF_COST2;
    FIELD_ARRAY[125] = Resource2Field::RF_COST3;
    FIELD_ARRAY[166] = Resource2Field::RF_COST4;
    FIELD_ARRAY[167] = Resource2Field::RF_COST5;
    FIELD_ARRAY[168] = Resource2Field::RF_COST6;
    FIELD_ARRAY[169] = Resource2Field::RF_COST7;
    FIELD_ARRAY[170] = Resource2Field::RF_COST8;
    FIELD_ARRAY[171] = Resource2Field::RF_COST9;
    FIELD_ARRAY[726] = Resource2Field::RF_CREATED;
    FIELD_ARRAY[268] = Resource2Field::RF_CV;
    FIELD_ARRAY[173] = Resource2Field::RF_DATE1;
    FIELD_ARRAY[182] = Resource2Field::RF_DATE10;
    FIELD_ARRAY[174] = Resource2Field::RF_DATE2;
    FIELD_ARRAY[175] = Resource2Field::RF_DATE3;
    FIELD_ARRAY[176] = Resource2Field::RF_DATE4;
    FIELD_ARRAY[177] = Resource2Field::RF_DATE5;
    FIELD_ARRAY[178] = Resource2Field::RF_DATE6;
    FIELD_ARRAY[179] = Resource2Field::RF_DATE7;
    FIELD_ARRAY[180] = Resource2Field::RF_DATE8;
    FIELD_ARRAY[740] = Resource2Field::RF_DEFAULT_ASSIGNMENT_OWNER;
    FIELD_ARRAY[117] = Resource2Field::RF_DURATION1;
    FIELD_ARRAY[189] = Resource2Field::RF_DURATION10;
    FIELD_ARRAY[118] = Resource2Field::RF_DURATION2;
    FIELD_ARRAY[119] = Resource2Field::RF_DURATION3;
    FIELD_ARRAY[183] = Resource2Field::RF_DURATION4;
    FIELD_ARRAY[184] = Resource2Field::RF_DURATION5;
    FIELD_ARRAY[185] = Resource2Field::RF_DURATION6;
    FIELD_ARRAY[186] = Resource2Field::RF_DURATION7;
    FIELD_ARRAY[187] = Resource2Field::RF_DURATION8;
    FIELD_ARRAY[188] = Resource2Field::RF_DURATION9;
    FIELD_ARRAY[35] = Resource2Field::RF_EMAIL_ADDRESS;
    FIELD_ARRAY[691] = Resource2Field::RF_ENTERPRISE;
    FIELD_ARRAY[687] = Resource2Field::RF_ENTERPRISE_BASE_CALENDAR;
    FIELD_ARRAY[446] = Resource2Field::RF_ENTERPRISE_COST1;
    FIELD_ARRAY[455] = Resource2Field::RF_ENTERPRISE_COST10;
    FIELD_ARRAY[447] = Resource2Field::RF_ENTERPRISE_COST2;
    FIELD_ARRAY[448] = Resource2Field::RF_ENTERPRISE_COST3;
    FIELD_ARRAY[449] = Resource2Field::RF_ENTERPRISE_COST4;
    FIELD_ARRAY[450] = Resource2Field::RF_ENTERPRISE_COST5;
    FIELD_ARRAY[451] = Resource2Field::RF_ENTERPRISE_COST6;
    FIELD_ARRAY[452] = Resource2Field::RF_ENTERPRISE_COST7;
    FIELD_ARRAY[453] = Resource2Field::RF_ENTERPRISE_COST8;
    FIELD_ARRAY[454] = Resource2Field::RF_ENTERPRISE_COST9;
    FIELD_ARRAY[456] = Resource2Field::RF_ENTERPRISE_DATE1;
    FIELD_ARRAY[465] = Resource2Field::RF_ENTERPRISE_DATE10;
    FIELD_ARRAY[466] = Resource2Field::RF_ENTERPRISE_DATE11;
    FIELD_ARRAY[467] = Resource2Field::RF_ENTERPRISE_DATE12;
    FIELD_ARRAY[468] = Resource2Field::RF_ENTERPRISE_DATE13;
    FIELD_ARRAY[469] = Resource2Field::RF_ENTERPRISE_DATE14;
    FIELD_ARRAY[470] = Resource2Field::RF_ENTERPRISE_DATE15;
    FIELD_ARRAY[471] = Resource2Field::RF_ENTERPRISE_DATE16;
    FIELD_ARRAY[472] = Resource2Field::RF_ENTERPRISE_DATE17;
    FIELD_ARRAY[473] = Resource2Field::RF_ENTERPRISE_DATE18;
    FIELD_ARRAY[474] = Resource2Field::RF_ENTERPRISE_DATE19;
    FIELD_ARRAY[457] = Resource2Field::RF_ENTERPRISE_DATE2;
    FIELD_ARRAY[475] = Resource2Field::RF_ENTERPRISE_DATE20;
    FIELD_ARRAY[476] = Resource2Field::RF_ENTERPRISE_DATE21;
    FIELD_ARRAY[477] = Resource2Field::RF_ENTERPRISE_DATE22;
    FIELD_ARRAY[478] = Resource2Field::RF_ENTERPRISE_DATE23;
    FIELD_ARRAY[479] = Resource2Field::RF_ENTERPRISE_DATE24;
    FIELD_ARRAY[480] = Resource2Field::RF_ENTERPRISE_DATE25;
    FIELD_ARRAY[481] = Resource2Field::RF_ENTERPRISE_DATE26;
    FIELD_ARRAY[482] = Resource2Field::RF_ENTERPRISE_DATE27;
    FIELD_ARRAY[483] = Resource2Field::RF_ENTERPRISE_DATE28;
    FIELD_ARRAY[484] = Resource2Field::RF_ENTERPRISE_DATE29;
    FIELD_ARRAY[458] = Resource2Field::RF_ENTERPRISE_DATE3;
    FIELD_ARRAY[485] = Resource2Field::RF_ENTERPRISE_DATE30;
    FIELD_ARRAY[459] = Resource2Field::RF_ENTERPRISE_DATE4;
    FIELD_ARRAY[460] = Resource2Field::RF_ENTERPRISE_DATE5;
    FIELD_ARRAY[461] = Resource2Field::RF_ENTERPRISE_DATE6;
    FIELD_ARRAY[462] = Resource2Field::RF_ENTERPRISE_DATE7;
    FIELD_ARRAY[463] = Resource2Field::RF_ENTERPRISE_DATE8;
    FIELD_ARRAY[464] = Resource2Field::RF_ENTERPRISE_DATE9;
    //FIELD_ARRAY[586] = Resource2Field::RF_ENTERPRISE_DEPARTMENT;
    FIELD_ARRAY[486] = Resource2Field::RF_ENTERPRISE_DURATION1;
    FIELD_ARRAY[495] = Resource2Field::RF_ENTERPRISE_DURATION10;
    FIELD_ARRAY[487] = Resource2Field::RF_ENTERPRISE_DURATION2;
    FIELD_ARRAY[488] = Resource2Field::RF_ENTERPRISE_DURATION3;
    FIELD_ARRAY[489] = Resource2Field::RF_ENTERPRISE_DURATION4;
    FIELD_ARRAY[490] = Resource2Field::RF_ENTERPRISE_DURATION5;
    FIELD_ARRAY[491] = Resource2Field::RF_ENTERPRISE_DURATION6;
    FIELD_ARRAY[492] = Resource2Field::RF_ENTERPRISE_DURATION7;
    FIELD_ARRAY[493] = Resource2Field::RF_ENTERPRISE_DURATION8;
    FIELD_ARRAY[494] = Resource2Field::RF_ENTERPRISE_DURATION9;
    FIELD_ARRAY[506] = Resource2Field::RF_ENTERPRISE_FLAG1;
    FIELD_ARRAY[515] = Resource2Field::RF_ENTERPRISE_FLAG10;
    FIELD_ARRAY[516] = Resource2Field::RF_ENTERPRISE_FLAG11;
    FIELD_ARRAY[517] = Resource2Field::RF_ENTERPRISE_FLAG12;
    FIELD_ARRAY[518] = Resource2Field::RF_ENTERPRISE_FLAG13;
    FIELD_ARRAY[519] = Resource2Field::RF_ENTERPRISE_FLAG14;
    FIELD_ARRAY[520] = Resource2Field::RF_ENTERPRISE_FLAG15;
    FIELD_ARRAY[521] = Resource2Field::RF_ENTERPRISE_FLAG16;
    FIELD_ARRAY[522] = Resource2Field::RF_ENTERPRISE_FLAG17;
    FIELD_ARRAY[523] = Resource2Field::RF_ENTERPRISE_FLAG18;
    FIELD_ARRAY[524] = Resource2Field::RF_ENTERPRISE_FLAG19;
    FIELD_ARRAY[507] = Resource2Field::RF_ENTERPRISE_FLAG2;
    FIELD_ARRAY[525] = Resource2Field::RF_ENTERPRISE_FLAG20;
    FIELD_ARRAY[508] = Resource2Field::RF_ENTERPRISE_FLAG3;
    FIELD_ARRAY[509] = Resource2Field::RF_ENTERPRISE_FLAG4;
    FIELD_ARRAY[510] = Resource2Field::RF_ENTERPRISE_FLAG5;
    FIELD_ARRAY[511] = Resource2Field::RF_ENTERPRISE_FLAG6;
    FIELD_ARRAY[512] = Resource2Field::RF_ENTERPRISE_FLAG7;
    FIELD_ARRAY[513] = Resource2Field::RF_ENTERPRISE_FLAG8;
    FIELD_ARRAY[514] = Resource2Field::RF_ENTERPRISE_FLAG9;
    FIELD_ARRAY[546] = Resource2Field::RF_ENTERPRISE_NUMBER1;
    FIELD_ARRAY[555] = Resource2Field::RF_ENTERPRISE_NUMBER10;
    FIELD_ARRAY[556] = Resource2Field::RF_ENTERPRISE_NUMBER11;
    FIELD_ARRAY[557] = Resource2Field::RF_ENTERPRISE_NUMBER12;
    FIELD_ARRAY[558] = Resource2Field::RF_ENTERPRISE_NUMBER13;
    FIELD_ARRAY[559] = Resource2Field::RF_ENTERPRISE_NUMBER14;
    FIELD_ARRAY[560] = Resource2Field::RF_ENTERPRISE_NUMBER15;
    FIELD_ARRAY[561] = Resource2Field::RF_ENTERPRISE_NUMBER16;
    FIELD_ARRAY[562] = Resource2Field::RF_ENTERPRISE_NUMBER17;
    FIELD_ARRAY[563] = Resource2Field::RF_ENTERPRISE_NUMBER18;
    FIELD_ARRAY[564] = Resource2Field::RF_ENTERPRISE_NUMBER19;
    FIELD_ARRAY[547] = Resource2Field::RF_ENTERPRISE_NUMBER2;
    FIELD_ARRAY[565] = Resource2Field::RF_ENTERPRISE_NUMBER20;
    FIELD_ARRAY[566] = Resource2Field::RF_ENTERPRISE_NUMBER21;
    FIELD_ARRAY[567] = Resource2Field::RF_ENTERPRISE_NUMBER22;
    FIELD_ARRAY[568] = Resource2Field::RF_ENTERPRISE_NUMBER23;
    FIELD_ARRAY[569] = Resource2Field::RF_ENTERPRISE_NUMBER24;
    FIELD_ARRAY[570] = Resource2Field::RF_ENTERPRISE_NUMBER25;
    FIELD_ARRAY[571] = Resource2Field::RF_ENTERPRISE_NUMBER26;
    FIELD_ARRAY[572] = Resource2Field::RF_ENTERPRISE_NUMBER27;
    FIELD_ARRAY[573] = Resource2Field::RF_ENTERPRISE_NUMBER28;
    FIELD_ARRAY[574] = Resource2Field::RF_ENTERPRISE_NUMBER29;
    FIELD_ARRAY[548] = Resource2Field::RF_ENTERPRISE_NUMBER3;
    FIELD_ARRAY[575] = Resource2Field::RF_ENTERPRISE_NUMBER30;
    FIELD_ARRAY[576] = Resource2Field::RF_ENTERPRISE_NUMBER31;
    FIELD_ARRAY[577] = Resource2Field::RF_ENTERPRISE_NUMBER32;
    FIELD_ARRAY[578] = Resource2Field::RF_ENTERPRISE_NUMBER33;
    FIELD_ARRAY[579] = Resource2Field::RF_ENTERPRISE_NUMBER34;
    FIELD_ARRAY[580] = Resource2Field::RF_ENTERPRISE_NUMBER35;
    FIELD_ARRAY[581] = Resource2Field::RF_ENTERPRISE_NUMBER36;
    FIELD_ARRAY[582] = Resource2Field::RF_ENTERPRISE_NUMBER37;
    FIELD_ARRAY[583] = Resource2Field::RF_ENTERPRISE_NUMBER38;
    FIELD_ARRAY[584] = Resource2Field::RF_ENTERPRISE_NUMBER39;
    FIELD_ARRAY[549] = Resource2Field::RF_ENTERPRISE_NUMBER4;
    FIELD_ARRAY[585] = Resource2Field::RF_ENTERPRISE_NUMBER40;
    FIELD_ARRAY[550] = Resource2Field::RF_ENTERPRISE_NUMBER5;
    FIELD_ARRAY[551] = Resource2Field::RF_ENTERPRISE_NUMBER6;
    FIELD_ARRAY[552] = Resource2Field::RF_ENTERPRISE_NUMBER7;
    FIELD_ARRAY[553] = Resource2Field::RF_ENTERPRISE_NUMBER8;
    FIELD_ARRAY[554] = Resource2Field::RF_ENTERPRISE_NUMBER9;
    FIELD_ARRAY[688] = Resource2Field::RF_ENTERPRISE_REQUIRED_VALUES;
    FIELD_ARRAY[695] = Resource2Field::RF_ENTERPRISE_TEAM_MEMBER;
    FIELD_ARRAY[646] = Resource2Field::RF_ENTERPRISE_TEXT1;
    FIELD_ARRAY[655] = Resource2Field::RF_ENTERPRISE_TEXT10;
    FIELD_ARRAY[656] = Resource2Field::RF_ENTERPRISE_TEXT11;
    FIELD_ARRAY[657] = Resource2Field::RF_ENTERPRISE_TEXT12;
    FIELD_ARRAY[658] = Resource2Field::RF_ENTERPRISE_TEXT13;
    FIELD_ARRAY[659] = Resource2Field::RF_ENTERPRISE_TEXT14;
    FIELD_ARRAY[660] = Resource2Field::RF_ENTERPRISE_TEXT15;
    FIELD_ARRAY[661] = Resource2Field::RF_ENTERPRISE_TEXT16;
    FIELD_ARRAY[662] = Resource2Field::RF_ENTERPRISE_TEXT17;
    FIELD_ARRAY[663] = Resource2Field::RF_ENTERPRISE_TEXT18;
    FIELD_ARRAY[664] = Resource2Field::RF_ENTERPRISE_TEXT19;
    FIELD_ARRAY[647] = Resource2Field::RF_ENTERPRISE_TEXT2;
    FIELD_ARRAY[665] = Resource2Field::RF_ENTERPRISE_TEXT20;
    FIELD_ARRAY[666] = Resource2Field::RF_ENTERPRISE_TEXT21;
    FIELD_ARRAY[667] = Resource2Field::RF_ENTERPRISE_TEXT22;
    FIELD_ARRAY[668] = Resource2Field::RF_ENTERPRISE_TEXT23;
    FIELD_ARRAY[669] = Resource2Field::RF_ENTERPRISE_TEXT24;
    FIELD_ARRAY[670] = Resource2Field::RF_ENTERPRISE_TEXT25;
    FIELD_ARRAY[671] = Resource2Field::RF_ENTERPRISE_TEXT26;
    FIELD_ARRAY[672] = Resource2Field::RF_ENTERPRISE_TEXT27;
    FIELD_ARRAY[673] = Resource2Field::RF_ENTERPRISE_TEXT28;
    FIELD_ARRAY[674] = Resource2Field::RF_ENTERPRISE_TEXT29;
    FIELD_ARRAY[648] = Resource2Field::RF_ENTERPRISE_TEXT3;
    FIELD_ARRAY[675] = Resource2Field::RF_ENTERPRISE_TEXT30;
    FIELD_ARRAY[676] = Resource2Field::RF_ENTERPRISE_TEXT31;
    FIELD_ARRAY[677] = Resource2Field::RF_ENTERPRISE_TEXT32;
    FIELD_ARRAY[678] = Resource2Field::RF_ENTERPRISE_TEXT33;
    FIELD_ARRAY[679] = Resource2Field::RF_ENTERPRISE_TEXT34;
    FIELD_ARRAY[680] = Resource2Field::RF_ENTERPRISE_TEXT35;
    FIELD_ARRAY[681] = Resource2Field::RF_ENTERPRISE_TEXT36;
    FIELD_ARRAY[682] = Resource2Field::RF_ENTERPRISE_TEXT37;
    FIELD_ARRAY[683] = Resource2Field::RF_ENTERPRISE_TEXT38;
    FIELD_ARRAY[684] = Resource2Field::RF_ENTERPRISE_TEXT39;
    FIELD_ARRAY[649] = Resource2Field::RF_ENTERPRISE_TEXT4;
    FIELD_ARRAY[685] = Resource2Field::RF_ENTERPRISE_TEXT40;
    FIELD_ARRAY[650] = Resource2Field::RF_ENTERPRISE_TEXT5;
    FIELD_ARRAY[651] = Resource2Field::RF_ENTERPRISE_TEXT6;
    FIELD_ARRAY[652] = Resource2Field::RF_ENTERPRISE_TEXT7;
    FIELD_ARRAY[653] = Resource2Field::RF_ENTERPRISE_TEXT8;
    FIELD_ARRAY[654] = Resource2Field::RF_ENTERPRISE_TEXT9;
    FIELD_ARRAY[443] = Resource2Field::RF_ENTERPRISE_UNIQUE_ID;
    FIELD_ARRAY[738] = Resource2Field::RF_ERROR_MESSAGE;
    FIELD_ARRAY[262] = Resource2Field::RF_FINISH;
    FIELD_ARRAY[107] = Resource2Field::RF_FINISH1;
    FIELD_ARRAY[194] = Resource2Field::RF_FINISH10;
    FIELD_ARRAY[108] = Resource2Field::RF_FINISH2;
    FIELD_ARRAY[109] = Resource2Field::RF_FINISH3;
    FIELD_ARRAY[110] = Resource2Field::RF_FINISH4;
    FIELD_ARRAY[111] = Resource2Field::RF_FINISH5;
    FIELD_ARRAY[190] = Resource2Field::RF_FINISH6;
    FIELD_ARRAY[191] = Resource2Field::RF_FINISH7;
    FIELD_ARRAY[192] = Resource2Field::RF_FINISH8;
    FIELD_ARRAY[193] = Resource2Field::RF_FINISH9;
    FIELD_ARRAY[127] = Resource2Field::RF_FLAG1;
    FIELD_ARRAY[126] = Resource2Field::RF_FLAG10;
    FIELD_ARRAY[195] = Resource2Field::RF_FLAG11;
    FIELD_ARRAY[196] = Resource2Field::RF_FLAG12;
    FIELD_ARRAY[197] = Resource2Field::RF_FLAG13;
    FIELD_ARRAY[198] = Resource2Field::RF_FLAG14;
    FIELD_ARRAY[199] = Resource2Field::RF_FLAG15;
    FIELD_ARRAY[200] = Resource2Field::RF_FLAG16;
    FIELD_ARRAY[201] = Resource2Field::RF_FLAG17;
    FIELD_ARRAY[202] = Resource2Field::RF_FLAG18;
    FIELD_ARRAY[203] = Resource2Field::RF_FLAG19;
    FIELD_ARRAY[128] = Resource2Field::RF_FLAG2;
    FIELD_ARRAY[204] = Resource2Field::RF_FLAG20;
    FIELD_ARRAY[129] = Resource2Field::RF_FLAG3;
    FIELD_ARRAY[130] = Resource2Field::RF_FLAG4;
    FIELD_ARRAY[131] = Resource2Field::RF_FLAG5;
    FIELD_ARRAY[132] = Resource2Field::RF_FLAG6;
    FIELD_ARRAY[133] = Resource2Field::RF_FLAG7;
    FIELD_ARRAY[134] = Resource2Field::RF_FLAG8;
    FIELD_ARRAY[135] = Resource2Field::RF_FLAG9;
    FIELD_ARRAY[686] = Resource2Field::RF_GENERIC;
    FIELD_ARRAY[3] = Resource2Field::RF_GROUP;
    FIELD_ARRAY[306] = Resource2Field::RF_GROUP_BY_SUMMARY;
    FIELD_ARRAY[728] = Resource2Field::RF_GUID;
    FIELD_ARRAY[138] = Resource2Field::RF_HYPERLINK;
    FIELD_ARRAY[139] = Resource2Field::RF_HYPERLINK_ADDRESS;
    FIELD_ARRAY[141] = Resource2Field::RF_HYPERLINK_HREF;
    FIELD_ARRAY[140] = Resource2Field::RF_HYPERLINK_SUBADDRESS;
    FIELD_ARRAY[0] = Resource2Field::RF_ID;
    FIELD_ARRAY[755] = Resource2Field::RF_IMPORT;
    FIELD_ARRAY[696] = Resource2Field::RF_INACTIVE;
    FIELD_ARRAY[86] = Resource2Field::RF_INDICATORS;
    FIELD_ARRAY[2] = Resource2Field::RF_INITIALS;
    FIELD_ARRAY[263] = Resource2Field::RF_LEVELING_DELAY;
    FIELD_ARRAY[34] = Resource2Field::RF_LINKED_FIELDS;
    FIELD_ARRAY[299] = Resource2Field::RF_MATERIAL_LABEL;
    FIELD_ARRAY[4] = Resource2Field::RF_MAX_UNITS;
    FIELD_ARRAY[1] = Resource2Field::RF_NAME;
    FIELD_ARRAY[28] = Resource2Field::RF_NOTES;
    FIELD_ARRAY[112] = Resource2Field::RF_NUMBER1;
    FIELD_ARRAY[209] = Resource2Field::RF_NUMBER10;
    FIELD_ARRAY[210] = Resource2Field::RF_NUMBER11;
    FIELD_ARRAY[211] = Resource2Field::RF_NUMBER12;
    FIELD_ARRAY[212] = Resource2Field::RF_NUMBER13;
    FIELD_ARRAY[213] = Resource2Field::RF_NUMBER14;
    FIELD_ARRAY[214] = Resource2Field::RF_NUMBER15;
    FIELD_ARRAY[215] = Resource2Field::RF_NUMBER16;
    FIELD_ARRAY[216] = Resource2Field::RF_NUMBER17;
    FIELD_ARRAY[217] = Resource2Field::RF_NUMBER18;
    FIELD_ARRAY[218] = Resource2Field::RF_NUMBER19;
    FIELD_ARRAY[113] = Resource2Field::RF_NUMBER2;
    FIELD_ARRAY[219] = Resource2Field::RF_NUMBER20;
    FIELD_ARRAY[114] = Resource2Field::RF_NUMBER3;
    FIELD_ARRAY[115] = Resource2Field::RF_NUMBER4;
    FIELD_ARRAY[116] = Resource2Field::RF_NUMBER5;
    FIELD_ARRAY[205] = Resource2Field::RF_NUMBER6;
    FIELD_ARRAY[206] = Resource2Field::RF_NUMBER7;
    FIELD_ARRAY[207] = Resource2Field::RF_NUMBER8;
    FIELD_ARRAY[208] = Resource2Field::RF_NUMBER9;
    FIELD_ARRAY[33] = Resource2Field::RF_OBJECTS;
    FIELD_ARRAY[278] = Resource2Field::RF_OUTLINE_CODE1;
    FIELD_ARRAY[296] = Resource2Field::RF_OUTLINE_CODE10;
    FIELD_ARRAY[280] = Resource2Field::RF_OUTLINE_CODE2;
    FIELD_ARRAY[282] = Resource2Field::RF_OUTLINE_CODE3;
    FIELD_ARRAY[284] = Resource2Field::RF_OUTLINE_CODE4;
    FIELD_ARRAY[286] = Resource2Field::RF_OUTLINE_CODE5;
    FIELD_ARRAY[288] = Resource2Field::RF_OUTLINE_CODE6;
    FIELD_ARRAY[290] = Resource2Field::RF_OUTLINE_CODE7;
    FIELD_ARRAY[292] = Resource2Field::RF_OUTLINE_CODE8;
    FIELD_ARRAY[294] = Resource2Field::RF_OUTLINE_CODE9;
    FIELD_ARRAY[25] = Resource2Field::RF_OVERALLOCATED;
    FIELD_ARRAY[47] = Resource2Field::RF_OVERTIME_COST;
    FIELD_ARRAY[7] = Resource2Field::RF_OVERTIME_RATE;
    FIELD_ARRAY[16] = Resource2Field::RF_OVERTIME_WORK;
    FIELD_ARRAY[26] = Resource2Field::RF_PEAK;
    FIELD_ARRAY[252] = Resource2Field::RF_PHONETICS;
    FIELD_ARRAY[273] = Resource2Field::RF_PROJECT;
    FIELD_ARRAY[38] = Resource2Field::RF_REGULAR_WORK;
    FIELD_ARRAY[21] = Resource2Field::RF_REMAINING_COST;
    FIELD_ARRAY[49] = Resource2Field::RF_REMAINING_OVERTIME_COST;
    FIELD_ARRAY[40] = Resource2Field::RF_REMAINING_OVERTIME_WORK;
    FIELD_ARRAY[22] = Resource2Field::RF_REMAINING_WORK;
    FIELD_ARRAY[690] = Resource2Field::RF_REQUEST_DEMAND;
    FIELD_ARRAY[264] = Resource2Field::RF_RESPONSE_PENDING;
    FIELD_ARRAY[6] = Resource2Field::RF_STANDARD_RATE;
    FIELD_ARRAY[265] = Resource2Field::RF_START;
    FIELD_ARRAY[102] = Resource2Field::RF_START1;
    FIELD_ARRAY[224] = Resource2Field::RF_START10;
    FIELD_ARRAY[103] = Resource2Field::RF_START2;
    FIELD_ARRAY[104] = Resource2Field::RF_START3;
    FIELD_ARRAY[105] = Resource2Field::RF_START4;
    FIELD_ARRAY[106] = Resource2Field::RF_START5;
    FIELD_ARRAY[220] = Resource2Field::RF_START6;
    FIELD_ARRAY[221] = Resource2Field::RF_START7;
    FIELD_ARRAY[222] = Resource2Field::RF_START8;
    FIELD_ARRAY[223] = Resource2Field::RF_START9;
    FIELD_ARRAY[737] = Resource2Field::RF_SUMMARY;
    FIELD_ARRAY[54] = Resource2Field::RF_SV;
    FIELD_ARRAY[442] = Resource2Field::RF_TASK_OUTLINE_NUMBER;
    FIELD_ARRAY[159] = Resource2Field::RF_TASK_SUMMARY_NAME;
    FIELD_ARRAY[800] = Resource2Field::RF_TEAM_ASSIGNMENT_POOL;
    FIELD_ARRAY[266] = Resource2Field::RF_TEAMSTATUS_PENDING;
    FIELD_ARRAY[8] = Resource2Field::RF_TEXT1;
    FIELD_ARRAY[101] = Resource2Field::RF_TEXT10;
    FIELD_ARRAY[225] = Resource2Field::RF_TEXT11;
    FIELD_ARRAY[226] = Resource2Field::RF_TEXT12;
    FIELD_ARRAY[227] = Resource2Field::RF_TEXT13;
    FIELD_ARRAY[228] = Resource2Field::RF_TEXT14;
    FIELD_ARRAY[229] = Resource2Field::RF_TEXT15;
    FIELD_ARRAY[230] = Resource2Field::RF_TEXT16;
    FIELD_ARRAY[231] = Resource2Field::RF_TEXT17;
    FIELD_ARRAY[232] = Resource2Field::RF_TEXT18;
    FIELD_ARRAY[233] = Resource2Field::RF_TEXT19;
    FIELD_ARRAY[9] = Resource2Field::RF_TEXT2;
    FIELD_ARRAY[234] = Resource2Field::RF_TEXT20;
    FIELD_ARRAY[235] = Resource2Field::RF_TEXT21;
    FIELD_ARRAY[236] = Resource2Field::RF_TEXT22;
    FIELD_ARRAY[237] = Resource2Field::RF_TEXT23;
    FIELD_ARRAY[238] = Resource2Field::RF_TEXT24;
    FIELD_ARRAY[239] = Resource2Field::RF_TEXT25;
    FIELD_ARRAY[240] = Resource2Field::RF_TEXT26;
    FIELD_ARRAY[241] = Resource2Field::RF_TEXT27;
    FIELD_ARRAY[242] = Resource2Field::RF_TEXT28;
    FIELD_ARRAY[243] = Resource2Field::RF_TEXT29;
    FIELD_ARRAY[30] = Resource2Field::RF_TEXT3;
    FIELD_ARRAY[244] = Resource2Field::RF_TEXT30;
    FIELD_ARRAY[31] = Resource2Field::RF_TEXT4;
    FIELD_ARRAY[32] = Resource2Field::RF_TEXT5;
    FIELD_ARRAY[97] = Resource2Field::RF_TEXT6;
    FIELD_ARRAY[98] = Resource2Field::RF_TEXT7;
    FIELD_ARRAY[99] = Resource2Field::RF_TEXT8;
    FIELD_ARRAY[100] = Resource2Field::RF_TEXT9;
    FIELD_ARRAY[300] = Resource2Field::RF_TYPE;
    FIELD_ARRAY[27] = Resource2Field::RF_UNIQUE_ID;
    FIELD_ARRAY[267] = Resource2Field::RF_UPDATE_NEEDED;
    FIELD_ARRAY[301] = Resource2Field::RF_VAC;
    FIELD_ARRAY[340] = Resource2Field::RF_WBS;
    FIELD_ARRAY[311] = Resource2Field::RF_WINDOWS_USER_ACCOUNT;
    FIELD_ARRAY[13] = Resource2Field::RF_WORK;
    FIELD_ARRAY[164] = Resource2Field::RF_WORK_CONTOUR;
    FIELD_ARRAY[23] = Resource2Field::RF_WORK_VARIANCE;

    FIELD_ARRAY[20] = Resource2Field::RF_NOTES;
    FIELD_ARRAY[181] = Resource2Field::RF_DATE9;
    FIELD_ARRAY[253] = Resource2Field::RF_INDEX;
    FIELD_ARRAY[272] = Resource2Field::RF_WORKGROUP;
    FIELD_ARRAY[312] = Resource2Field::RF_HYPERLINK_SCREEN_TIP;
    FIELD_ARRAY[586] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE1;
    FIELD_ARRAY[588] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE2;
    FIELD_ARRAY[590] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE3;
    FIELD_ARRAY[592] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE4;
    FIELD_ARRAY[594] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE5;
    FIELD_ARRAY[596] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE6;
    FIELD_ARRAY[598] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE7;
    FIELD_ARRAY[600] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE8;
    FIELD_ARRAY[602] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE9;
    FIELD_ARRAY[604] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE10;
    FIELD_ARRAY[606] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE11;
    FIELD_ARRAY[608] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE12;
    FIELD_ARRAY[610] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE13;
    FIELD_ARRAY[612] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE14;
    FIELD_ARRAY[614] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE15;
    FIELD_ARRAY[616] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE16;
    FIELD_ARRAY[618] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE17;
    FIELD_ARRAY[620] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE18;
    FIELD_ARRAY[622] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE19;
    FIELD_ARRAY[624] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE20;
    FIELD_ARRAY[626] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE21;
    FIELD_ARRAY[628] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE22;
    FIELD_ARRAY[630] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE23;
    FIELD_ARRAY[632] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE24;
    FIELD_ARRAY[634] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE25;
    FIELD_ARRAY[636] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE26;
    FIELD_ARRAY[638] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE27;
    FIELD_ARRAY[640] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE28;
    FIELD_ARRAY[642] = Resource2Field::RF_ENTERPRISE_OUTLINE_CODE29;
    FIELD_ARRAY[644] = Resource2Field::RF_ENTERPRISE_RBS;
    FIELD_ARRAY[689] = Resource2Field::RF_ENTERPRISE_NAME_USED;
    FIELD_ARRAY[692] = Resource2Field::RF_ENTERPRISE_IS_CHECKED_OUT;
    FIELD_ARRAY[693] = Resource2Field::RF_ENTERPRISE_CHECKED_OUT_BY;
    FIELD_ARRAY[694] = Resource2Field::RF_ENTERPRISE_LAST_MODIFIED_DATE;
    FIELD_ARRAY[700] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE20;
    FIELD_ARRAY[702] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE21;
    FIELD_ARRAY[704] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE22;
    FIELD_ARRAY[706] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE23;
    FIELD_ARRAY[708] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE24;
    FIELD_ARRAY[710] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE25;
    FIELD_ARRAY[712] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE26;
    FIELD_ARRAY[714] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE27;
    FIELD_ARRAY[716] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE28;
    FIELD_ARRAY[718] = Resource2Field::RF_ENTERPRISE_MULTI_VALUE29;
    FIELD_ARRAY[720] = Resource2Field::RF_ACTUAL_WORK_PROTECTED;
    FIELD_ARRAY[721] = Resource2Field::RF_ACTUAL_OVERTIME_WORK_PROTECTED;

    FIELD_ARRAY[61] = Resource2Field::RF_COST_RATE_A;
    FIELD_ARRAY[62] = Resource2Field::RF_COST_RATE_B;
    FIELD_ARRAY[63] = Resource2Field::RF_COST_RATE_C;
    FIELD_ARRAY[64] = Resource2Field::RF_COST_RATE_D;
    FIELD_ARRAY[65] = Resource2Field::RF_COST_RATE_E;
    FIELD_ARRAY[70] = Resource2Field::RF_STANDARD_RATE_UNITS;
    FIELD_ARRAY[71] = Resource2Field::RF_OVERTIME_RATE_UNITS;
    FIELD_ARRAY[120] = Resource2Field::RF_DURATION1_UNITS;
    FIELD_ARRAY[121] = Resource2Field::RF_DURATION2_UNITS;
    FIELD_ARRAY[122] = Resource2Field::RF_DURATION3_UNITS;
    FIELD_ARRAY[245] = Resource2Field::RF_DURATION4_UNITS;
    FIELD_ARRAY[246] = Resource2Field::RF_DURATION5_UNITS;
    FIELD_ARRAY[247] = Resource2Field::RF_DURATION6_UNITS;
    FIELD_ARRAY[248] = Resource2Field::RF_DURATION7_UNITS;
    FIELD_ARRAY[249] = Resource2Field::RF_DURATION8_UNITS;
    FIELD_ARRAY[250] = Resource2Field::RF_DURATION9_UNITS;
    FIELD_ARRAY[251] = Resource2Field::RF_DURATION10_UNITS;
    FIELD_ARRAY[496] = Resource2Field::RF_ENTERPRISE_DURATION1_UNITS;
    FIELD_ARRAY[497] = Resource2Field::RF_ENTERPRISE_DURATION2_UNITS;
    FIELD_ARRAY[498] = Resource2Field::RF_ENTERPRISE_DURATION3_UNITS;
    FIELD_ARRAY[499] = Resource2Field::RF_ENTERPRISE_DURATION4_UNITS;
    FIELD_ARRAY[500] = Resource2Field::RF_ENTERPRISE_DURATION5_UNITS;
    FIELD_ARRAY[501] = Resource2Field::RF_ENTERPRISE_DURATION6_UNITS;
    FIELD_ARRAY[502] = Resource2Field::RF_ENTERPRISE_DURATION7_UNITS;
    FIELD_ARRAY[503] = Resource2Field::RF_ENTERPRISE_DURATION8_UNITS;
    FIELD_ARRAY[504] = Resource2Field::RF_ENTERPRISE_DURATION9_UNITS;
    FIELD_ARRAY[505] = Resource2Field::RF_ENTERPRISE_DURATION10_UNITS;
    FIELD_ARRAY[279] = Resource2Field::RF_OUTLINE_CODE1_INDEX;
    FIELD_ARRAY[281] = Resource2Field::RF_OUTLINE_CODE2_INDEX;
    FIELD_ARRAY[283] = Resource2Field::RF_OUTLINE_CODE3_INDEX;
    FIELD_ARRAY[285] = Resource2Field::RF_OUTLINE_CODE4_INDEX;
    FIELD_ARRAY[287] = Resource2Field::RF_OUTLINE_CODE5_INDEX;
    FIELD_ARRAY[289] = Resource2Field::RF_OUTLINE_CODE6_INDEX;
    FIELD_ARRAY[291] = Resource2Field::RF_OUTLINE_CODE7_INDEX;
    FIELD_ARRAY[293] = Resource2Field::RF_OUTLINE_CODE8_INDEX;
    FIELD_ARRAY[295] = Resource2Field::RF_OUTLINE_CODE9_INDEX;
    FIELD_ARRAY[297] = Resource2Field::RF_OUTLINE_CODE10_INDEX;
    FIELD_ARRAY[136] = Resource2Field::RF_HYPERLINK_DATA;
    FIELD_ARRAY[276] = Resource2Field::RF_AVAILABILITY_DATA;

	for (int loop = 0; loop < MAX_VALUE; loop++)
	{
		Resource2Field resourceField = FIELD_ARRAY[loop];
		if (resourceField != (Resource2Field)- 1)
		{
			ID_ARRAY[resourceField] = loop;
		}
	}
}

Resource2Field MPPResource2Field14::FIELD_ARRAY[MAX_VALUE] = { (Resource2Field)- 1 };
int MPPResource2Field14::ID_ARRAY[Resource2Field::RF_FINISH+1] = { -1 };
