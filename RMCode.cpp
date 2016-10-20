#include <stdio.h>
#include <stdlib.h>
#include <time.h>	//time

void rmIdxCalculator(unsigned short *array, const short& arrayLen, unsigned short& arrayPointer, unsigned short *result, unsigned short& resultIdx, unsigned short& resultValue);
void rmSCalculate(unsigned short *row, const short& rowLength, unsigned short *S);
void rmECalculate(unsigned short *row, const short& rowLength, const short& m, unsigned short *E);
void rmSCCalculate(unsigned short *row, const short& rowLength, unsigned short *SC);
unsigned char rmDecision(unsigned short *array, unsigned short arrayLength);
unsigned char rmACalculate(unsigned short& SLength, unsigned short *S, const unsigned short& SCLength, unsigned short *SC, unsigned char **codeword);
void rmDecoding(const short& n, const short& m, const short& rowLength, unsigned short* row, short rowIdx, short& rowValue, unsigned char **codeword, unsigned char **recovery, unsigned short& recoveryIdx);
void rmRUpdate(unsigned short& start, unsigned short& end, unsigned char **recovery, unsigned char **G, unsigned char **codeword, const unsigned short& n);
void rmDecoder(const unsigned short& r, const unsigned short& m, unsigned char **GRM, const unsigned short& n, unsigned char **codeword, unsigned char **recovery);
void rmEncoder(const unsigned short k, unsigned char **msg, const unsigned short n, unsigned char **G, unsigned char **codeword);


unsigned short power(const unsigned short& exponent);
unsigned short combination(unsigned short n, const unsigned short& k);
void mtrixMultiplication(const unsigned int& pRow, const unsigned int& pCol, unsigned char** prev, const unsigned int& nRow, const unsigned int& nCol, unsigned char** next, unsigned char** result);
void errorGenerator(const unsigned int& weight, const unsigned int& size, unsigned char* error);
void errorAdd(const unsigned int& size, unsigned char* original, unsigned char* error, unsigned char* result);
void grm(const short& n, const short& m, const short& lim, unsigned char** matrix, unsigned short& idx, short *row, short rowIdx, short& rowValue);
void generateMatrix(const short& r, const short& m, const short& n, unsigned char **matrix);


double* rcsvRight(int r, int m, double *orgMsg, int orgMsgLength, double *result, int resultLength);
double* rcsvLeft(int r, int m, double *orgMsg, int orgMsgLength, double *v, int vLength, double *result, int resultLength);
void rcsvDecisionZero(double *orgMsg, int orgMsgLength, double *result, int resultLength);
void rcsvDecisionEqual(double *orgMsg, int orgMsgLength, double *result, int resultLength);
void rcsvDecodingHard(int r, int m, unsigned char *recvCodeword, int recvCodewordLength);

void main()
{
	unsigned short r = 4; //4;
	unsigned short m = 10; //10;

	unsigned short n = 0; //code length
	unsigned short k = 0; //message length	

	unsigned short t = 31;
	
	srand((unsigned)time(NULL));

	n = power(m);
	for (int i = 0; i <= r; i++)
	{
		k += combination(m, i);
	}

	printf("n = %d, k = %d\n\n", n, k);


	unsigned char **G = (unsigned char **)malloc(sizeof(unsigned char *) * k);

	for (int i = 0; i < k; i++)
	{
		G[i] = (unsigned char *)malloc(sizeof(unsigned char) * n);
		for (int j = 0; j<n; j++)
		{
			G[i][j] = 1;
		}
	}


	generateMatrix(r, m, n, G); //generate G
	/*printf("\nG\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n"); printf("\n");*/

for(int test=0; test < 1000; test++)
{
	unsigned char **msg = (unsigned char **)malloc(sizeof(unsigned char *) * 1);
	msg[0] = (unsigned char *)malloc(sizeof(unsigned char) * k);
	for (int i = 0; i < k; i++)
	{
		msg[0][i] = rand() % 2;
	}
	
	
	/*msg[0][0] = 0;	msg[0][1] = 1;	msg[0][2] = 0;	msg[0][3] = 0;	msg[0][4] = 1;	msg[0][5] = 0;	msg[0][6] = 0;	msg[0][7] = 1;	msg[0][8] = 0;	msg[0][9] = 0;	msg[0][10] = 1;	msg[0][11] = 0;	msg[0][12] = 0;	msg[0][13] = 1;	msg[0][14] = 1;	msg[0][15] = 1;	msg[0][16] = 0;	msg[0][17] = 1;	msg[0][18] = 1;	msg[0][19] = 0;	msg[0][20] = 0;	msg[0][21] = 0;	msg[0][22] = 0;	msg[0][23] = 0;	msg[0][24] = 1;	msg[0][25] = 0;	msg[0][26] = 0;	msg[0][27] = 1;	msg[0][28] = 0;	msg[0][29] = 1;	msg[0][30] = 1;	msg[0][31] = 1;	msg[0][32] = 1;	msg[0][33] = 0;	msg[0][34] = 0;	msg[0][35] = 0;	msg[0][36] = 1;	msg[0][37] = 1;	msg[0][38] = 0;	msg[0][39] = 1;	msg[0][40] = 0;	msg[0][41] = 0;	msg[0][42] = 1;	msg[0][43] = 0;	msg[0][44] = 0;	msg[0][45] = 1;	msg[0][46] = 0;	msg[0][47] = 0;	msg[0][48] = 1;	msg[0][49] = 1;	msg[0][50] = 1;	msg[0][51] = 0;	msg[0][52] = 0;	msg[0][53] = 0;	msg[0][54] = 0;	msg[0][55] = 0;	msg[0][56] = 1;	msg[0][57] = 1;	msg[0][58] = 1;	msg[0][59] = 1;	msg[0][60] = 1;	msg[0][61] = 1;	msg[0][62] = 1;	msg[0][63] = 0;	msg[0][64] = 0;	msg[0][65] = 0;	msg[0][66] = 1;	msg[0][67] = 1;	msg[0][68] = 0;	msg[0][69] = 1;	msg[0][70] = 0;	msg[0][71] = 1;	msg[0][72] = 0;	msg[0][73] = 1;	msg[0][74] = 1;	msg[0][75] = 0;	msg[0][76] = 0;	msg[0][77] = 0;	msg[0][78] = 1;	msg[0][79] = 0;	msg[0][80] = 0;	msg[0][81] = 1;	msg[0][82] = 1;	msg[0][83] = 0;	msg[0][84] = 0;	msg[0][85] = 0;	msg[0][86] = 0;	msg[0][87] = 1;	msg[0][88] = 0;	msg[0][89] = 1;	msg[0][90] = 0;	msg[0][91] = 0;	msg[0][92] = 1;	msg[0][93] = 1;	msg[0][94] = 1;	msg[0][95] = 1;	msg[0][96] = 0;	msg[0][97] = 0;	msg[0][98] = 0;	msg[0][99] = 0;	msg[0][100] = 1;	msg[0][101] = 1;	msg[0][102] = 0;	msg[0][103] = 1;	msg[0][104] = 0;	msg[0][105] = 0;	msg[0][106] = 1;	msg[0][107] = 1;	msg[0][108] = 1;	msg[0][109] = 0;	msg[0][110] = 0;	msg[0][111] = 1;	msg[0][112] = 0;	msg[0][113] = 1;	msg[0][114] = 1;	msg[0][115] = 1;	msg[0][116] = 0;	msg[0][117] = 1;	msg[0][118] = 1;	msg[0][119] = 1;	msg[0][120] = 0;	msg[0][121] = 1;	msg[0][122] = 0;	msg[0][123] = 1;	msg[0][124] = 1;	msg[0][125] = 0;	msg[0][126] = 1;	msg[0][127] = 1;	msg[0][128] = 0;	msg[0][129] = 0;	msg[0][130] = 1;	msg[0][131] = 1;	msg[0][132] = 1;	msg[0][133] = 1;	msg[0][134] = 0;	msg[0][135] = 1;	msg[0][136] = 1;	msg[0][137] = 1;	msg[0][138] = 0;	msg[0][139] = 1;	msg[0][140] = 0;	msg[0][141] = 0;	msg[0][142] = 1;	msg[0][143] = 1;	msg[0][144] = 1;	msg[0][145] = 1;	msg[0][146] = 0;	msg[0][147] = 1;	msg[0][148] = 1;	msg[0][149] = 0;	msg[0][150] = 1;	msg[0][151] = 1;	msg[0][152] = 0;	msg[0][153] = 1;	msg[0][154] = 0;	msg[0][155] = 1;	msg[0][156] = 1;	msg[0][157] = 1;	msg[0][158] = 1;	msg[0][159] = 1;	msg[0][160] = 0;	msg[0][161] = 1;	msg[0][162] = 0;	msg[0][163] = 0;	msg[0][164] = 1;	msg[0][165] = 1;	msg[0][166] = 1;	msg[0][167] = 0;	msg[0][168] = 0;	msg[0][169] = 1;	msg[0][170] = 0;	msg[0][171] = 0;	msg[0][172] = 1;	msg[0][173] = 1;	msg[0][174] = 0;	msg[0][175] = 0;	msg[0][176] = 0;	msg[0][177] = 0;	msg[0][178] = 0;	msg[0][179] = 1;	msg[0][180] = 1;	msg[0][181] = 1;	msg[0][182] = 1;	msg[0][183] = 0;	msg[0][184] = 0;	msg[0][185] = 0;	msg[0][186] = 0;	msg[0][187] = 0;	msg[0][188] = 0;	msg[0][189] = 0;	msg[0][190] = 1;	msg[0][191] = 1;	msg[0][192] = 0;	msg[0][193] = 0;	msg[0][194] = 1;	msg[0][195] = 0;	msg[0][196] = 0;	msg[0][197] = 1;	msg[0][198] = 1;	msg[0][199] = 1;	msg[0][200] = 1;	msg[0][201] = 1;	msg[0][202] = 1;	msg[0][203] = 1;	msg[0][204] = 1;	msg[0][205] = 0;	msg[0][206] = 0;	msg[0][207] = 1;	msg[0][208] = 0;	msg[0][209] = 1;	msg[0][210] = 1;	msg[0][211] = 1;	msg[0][212] = 0;	msg[0][213] = 1;	msg[0][214] = 0;	msg[0][215] = 1;	msg[0][216] = 1;	msg[0][217] = 1;	msg[0][218] = 0;	msg[0][219] = 0;	msg[0][220] = 1;	msg[0][221] = 0;	msg[0][222] = 1;	msg[0][223] = 1;	msg[0][224] = 1;	msg[0][225] = 1;	msg[0][226] = 0;	msg[0][227] = 1;	msg[0][228] = 0;	msg[0][229] = 1;	msg[0][230] = 0;	msg[0][231] = 0;	msg[0][232] = 0;	msg[0][233] = 1;	msg[0][234] = 1;	msg[0][235] = 1;	msg[0][236] = 0;	msg[0][237] = 1;	msg[0][238] = 1;	msg[0][239] = 1;	msg[0][240] = 0;	msg[0][241] = 1;	msg[0][242] = 1;	msg[0][243] = 1;	msg[0][244] = 1;	msg[0][245] = 0;	msg[0][246] = 0;	msg[0][247] = 0;	msg[0][248] = 1;	msg[0][249] = 0;	msg[0][250] = 0;	msg[0][251] = 1;	msg[0][252] = 1;	msg[0][253] = 1;	msg[0][254] = 0;	msg[0][255] = 1;	msg[0][256] = 1;	msg[0][257] = 1;	msg[0][258] = 1;	msg[0][259] = 1;	msg[0][260] = 1;	msg[0][261] = 1;	msg[0][262] = 0;	msg[0][263] = 1;	msg[0][264] = 0;	msg[0][265] = 1;	msg[0][266] = 0;	msg[0][267] = 1;	msg[0][268] = 1;	msg[0][269] = 0;	msg[0][270] = 0;	msg[0][271] = 0;	msg[0][272] = 1;	msg[0][273] = 1;	msg[0][274] = 0;	msg[0][275] = 0;	msg[0][276] = 1;	msg[0][277] = 1;	msg[0][278] = 1;	msg[0][279] = 1;	msg[0][280] = 0;	msg[0][281] = 0;	msg[0][282] = 0;	msg[0][283] = 1;	msg[0][284] = 1;	msg[0][285] = 0;	msg[0][286] = 0;	msg[0][287] = 0;	msg[0][288] = 1;	msg[0][289] = 1;	msg[0][290] = 0;	msg[0][291] = 1;	msg[0][292] = 0;	msg[0][293] = 1;	msg[0][294] = 1;	msg[0][295] = 0;	msg[0][296] = 1;	msg[0][297] = 0;	msg[0][298] = 0;	msg[0][299] = 0;	msg[0][300] = 0;	msg[0][301] = 1;	msg[0][302] = 0;	msg[0][303] = 0;	msg[0][304] = 1;	msg[0][305] = 1;	msg[0][306] = 1;	msg[0][307] = 0;	msg[0][308] = 1;	msg[0][309] = 1;	msg[0][310] = 1;	msg[0][311] = 1;	msg[0][312] = 0;	msg[0][313] = 0;	msg[0][314] = 1;	msg[0][315] = 1;	msg[0][316] = 1;	msg[0][317] = 0;	msg[0][318] = 0;	msg[0][319] = 1;	msg[0][320] = 0;	msg[0][321] = 1;	msg[0][322] = 0;	msg[0][323] = 0;	msg[0][324] = 1;	msg[0][325] = 1;	msg[0][326] = 0;	msg[0][327] = 0;	msg[0][328] = 0;	msg[0][329] = 1;	msg[0][330] = 0;	msg[0][331] = 1;	msg[0][332] = 0;	msg[0][333] = 1;	msg[0][334] = 1;	msg[0][335] = 1;	msg[0][336] = 1;	msg[0][337] = 1;	msg[0][338] = 0;	msg[0][339] = 1;	msg[0][340] = 0;	msg[0][341] = 0;	msg[0][342] = 0;	msg[0][343] = 0;	msg[0][344] = 0;	msg[0][345] = 0;	msg[0][346] = 0;	msg[0][347] = 0;	msg[0][348] = 0;	msg[0][349] = 1;	msg[0][350] = 1;	msg[0][351] = 1;	msg[0][352] = 1;	msg[0][353] = 0;	msg[0][354] = 0;	msg[0][355] = 0;	msg[0][356] = 1;	msg[0][357] = 1;	msg[0][358] = 0;	msg[0][359] = 0;	msg[0][360] = 1;	msg[0][361] = 0;	msg[0][362] = 0;	msg[0][363] = 1;	msg[0][364] = 0;	msg[0][365] = 0;	msg[0][366] = 1;	msg[0][367] = 0;	msg[0][368] = 1;	msg[0][369] = 0;	msg[0][370] = 0;	msg[0][371] = 0;	msg[0][372] = 0;	msg[0][373] = 0;	msg[0][374] = 1;	msg[0][375] = 0;	msg[0][376] = 0;	msg[0][377] = 1;	msg[0][378] = 1;	msg[0][379] = 0;	msg[0][380] = 0;	msg[0][381] = 0;	msg[0][382] = 1;	msg[0][383] = 1;	msg[0][384] = 1;	msg[0][385] = 1;

	printf("msg : \n");
	for (int i = 0; i < k; i++)
	{
		printf("%d ", msg[0][i]);
	}
	printf("\n");*/

	unsigned char **codeword = (unsigned char **)malloc(sizeof(unsigned char *) * 1);
	codeword[0] = (unsigned char *)malloc(sizeof(unsigned char) * n);
	rmEncoder(k, msg, n, G, codeword);


	//printf("codeword : \n");
	//for (int i = 0; i < n; i++)
	//{
	//	printf("%d ", codeword[0][i]);
	//}
	//printf("\n");

	/*add error*/
	unsigned char **error = (unsigned char **)malloc(sizeof(unsigned char *) * 1);
	error[0] = (unsigned char *)malloc(sizeof(unsigned char) * n);
	for (int i = 0; i < n; i++)
	{
		error[0][i] = 0;
	}
	errorGenerator(t, n, error[0]);

	unsigned char **errorCodeword = (unsigned char **)malloc(sizeof(unsigned char *) * 1);
	errorCodeword[0] = (unsigned char *)malloc(sizeof(unsigned char) * n);

	errorAdd(n, codeword[0], error[0], errorCodeword[0]);
	
	/*printf("errorCodeword : \n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", errorCodeword[0][i]);
	}*/
	//printf("\n");
	free(error[0]);
	free(error);


	//rcsvDecodingHard(r, m, errorCodeword[0], n);

	unsigned char **recovery = (unsigned char **)malloc(sizeof(unsigned char *) * 1);
	recovery[0] = (unsigned char *)malloc(sizeof(unsigned char) * k);
	
	//errorCodeword[0][0] = 0;	errorCodeword[0][1] = 1;	errorCodeword[0][2] = 0;	errorCodeword[0][3] = 0;	errorCodeword[0][4] = 0;	errorCodeword[0][5] = 0;	errorCodeword[0][6] = 1;	errorCodeword[0][7] = 0;	errorCodeword[0][8] = 1;	errorCodeword[0][9] = 1;	errorCodeword[0][10] = 1;	errorCodeword[0][11] = 1;	errorCodeword[0][12] = 1;	errorCodeword[0][13] = 0;	errorCodeword[0][14] = 1;	errorCodeword[0][15] = 1;	errorCodeword[0][16] = 0;	errorCodeword[0][17] = 1;	errorCodeword[0][18] = 1;	errorCodeword[0][19] = 0;	errorCodeword[0][20] = 1;	errorCodeword[0][21] = 0;	errorCodeword[0][22] = 0;	errorCodeword[0][23] = 1;	errorCodeword[0][24] = 1;	errorCodeword[0][25] = 0;	errorCodeword[0][26] = 0;	errorCodeword[0][27] = 0;	errorCodeword[0][28] = 1;	errorCodeword[0][29] = 1;	errorCodeword[0][30] = 1;	errorCodeword[0][31] = 0;	errorCodeword[0][32] = 0;	errorCodeword[0][33] = 1;	errorCodeword[0][34] = 1;	errorCodeword[0][35] = 1;	errorCodeword[0][36] = 0;	errorCodeword[0][37] = 1;	errorCodeword[0][38] = 0;	errorCodeword[0][39] = 1;	errorCodeword[0][40] = 1;	errorCodeword[0][41] = 1;	errorCodeword[0][42] = 0;	errorCodeword[0][43] = 0;	errorCodeword[0][44] = 0;	errorCodeword[0][45] = 1;	errorCodeword[0][46] = 1;	errorCodeword[0][47] = 0;	errorCodeword[0][48] = 0;	errorCodeword[0][49] = 0;	errorCodeword[0][50] = 0;	errorCodeword[0][51] = 1;	errorCodeword[0][52] = 1;	errorCodeword[0][53] = 1;	errorCodeword[0][54] = 0;	errorCodeword[0][55] = 0;	errorCodeword[0][56] = 0;	errorCodeword[0][57] = 0;	errorCodeword[0][58] = 1;	errorCodeword[0][59] = 1;	errorCodeword[0][60] = 1;	errorCodeword[0][61] = 1;	errorCodeword[0][62] = 1;	errorCodeword[0][63] = 1;	errorCodeword[0][64] = 1;	errorCodeword[0][65] = 0;	errorCodeword[0][66] = 1;	errorCodeword[0][67] = 1;	errorCodeword[0][68] = 1;	errorCodeword[0][69] = 1;	errorCodeword[0][70] = 1;	errorCodeword[0][71] = 1;	errorCodeword[0][72] = 0;	errorCodeword[0][73] = 0;	errorCodeword[0][74] = 1;	errorCodeword[0][75] = 0;	errorCodeword[0][76] = 0;	errorCodeword[0][77] = 1;	errorCodeword[0][78] = 0;	errorCodeword[0][79] = 0;	errorCodeword[0][80] = 0;	errorCodeword[0][81] = 0;	errorCodeword[0][82] = 1;	errorCodeword[0][83] = 0;	errorCodeword[0][84] = 0;	errorCodeword[0][85] = 0;	errorCodeword[0][86] = 0;	errorCodeword[0][87] = 1;	errorCodeword[0][88] = 0;	errorCodeword[0][89] = 1;	errorCodeword[0][90] = 1;	errorCodeword[0][91] = 0;	errorCodeword[0][92] = 0;	errorCodeword[0][93] = 0;	errorCodeword[0][94] = 1;	errorCodeword[0][95] = 0;	errorCodeword[0][96] = 1;	errorCodeword[0][97] = 1;	errorCodeword[0][98] = 1;	errorCodeword[0][99] = 0;	errorCodeword[0][100] = 1;	errorCodeword[0][101] = 1;	errorCodeword[0][102] = 0;	errorCodeword[0][103] = 0;	errorCodeword[0][104] = 0;	errorCodeword[0][105] = 1;	errorCodeword[0][106] = 0;	errorCodeword[0][107] = 0;	errorCodeword[0][108] = 1;	errorCodeword[0][109] = 0;	errorCodeword[0][110] = 0;	errorCodeword[0][111] = 0;	errorCodeword[0][112] = 1;	errorCodeword[0][113] = 1;	errorCodeword[0][114] = 0;	errorCodeword[0][115] = 0;	errorCodeword[0][116] = 0;	errorCodeword[0][117] = 1;	errorCodeword[0][118] = 1;	errorCodeword[0][119] = 1;	errorCodeword[0][120] = 0;	errorCodeword[0][121] = 1;	errorCodeword[0][122] = 1;	errorCodeword[0][123] = 0;	errorCodeword[0][124] = 1;	errorCodeword[0][125] = 0;	errorCodeword[0][126] = 1;	errorCodeword[0][127] = 0;	errorCodeword[0][128] = 0;	errorCodeword[0][129] = 1;	errorCodeword[0][130] = 1;	errorCodeword[0][131] = 0;	errorCodeword[0][132] = 0;	errorCodeword[0][133] = 1;	errorCodeword[0][134] = 0;	errorCodeword[0][135] = 1;	errorCodeword[0][136] = 1;	errorCodeword[0][137] = 1;	errorCodeword[0][138] = 1;	errorCodeword[0][139] = 0;	errorCodeword[0][140] = 1;	errorCodeword[0][141] = 1;	errorCodeword[0][142] = 0;	errorCodeword[0][143] = 0;	errorCodeword[0][144] = 1;	errorCodeword[0][145] = 0;	errorCodeword[0][146] = 1;	errorCodeword[0][147] = 0;	errorCodeword[0][148] = 0;	errorCodeword[0][149] = 1;	errorCodeword[0][150] = 1;	errorCodeword[0][151] = 0;	errorCodeword[0][152] = 1;	errorCodeword[0][153] = 0;	errorCodeword[0][154] = 0;	errorCodeword[0][155] = 0;	errorCodeword[0][156] = 1;	errorCodeword[0][157] = 1;	errorCodeword[0][158] = 0;	errorCodeword[0][159] = 0;	errorCodeword[0][160] = 0;	errorCodeword[0][161] = 1;	errorCodeword[0][162] = 1;	errorCodeword[0][163] = 0;	errorCodeword[0][164] = 0;	errorCodeword[0][165] = 1;	errorCodeword[0][166] = 0;	errorCodeword[0][167] = 1;	errorCodeword[0][168] = 1;	errorCodeword[0][169] = 0;	errorCodeword[0][170] = 1;	errorCodeword[0][171] = 1;	errorCodeword[0][172] = 1;	errorCodeword[0][173] = 0;	errorCodeword[0][174] = 1;	errorCodeword[0][175] = 1;	errorCodeword[0][176] = 0;	errorCodeword[0][177] = 1;	errorCodeword[0][178] = 0;	errorCodeword[0][179] = 0;	errorCodeword[0][180] = 0;	errorCodeword[0][181] = 1;	errorCodeword[0][182] = 1;	errorCodeword[0][183] = 0;	errorCodeword[0][184] = 0;	errorCodeword[0][185] = 0;	errorCodeword[0][186] = 0;	errorCodeword[0][187] = 0;	errorCodeword[0][188] = 0;	errorCodeword[0][189] = 0;	errorCodeword[0][190] = 0;	errorCodeword[0][191] = 0;	errorCodeword[0][192] = 1;	errorCodeword[0][193] = 0;	errorCodeword[0][194] = 1;	errorCodeword[0][195] = 1;	errorCodeword[0][196] = 1;	errorCodeword[0][197] = 0;	errorCodeword[0][198] = 0;	errorCodeword[0][199] = 0;	errorCodeword[0][200] = 0;	errorCodeword[0][201] = 0;	errorCodeword[0][202] = 1;	errorCodeword[0][203] = 0;	errorCodeword[0][204] = 1;	errorCodeword[0][205] = 0;	errorCodeword[0][206] = 0;	errorCodeword[0][207] = 1;	errorCodeword[0][208] = 1;	errorCodeword[0][209] = 0;	errorCodeword[0][210] = 1;	errorCodeword[0][211] = 0;	errorCodeword[0][212] = 1;	errorCodeword[0][213] = 1;	errorCodeword[0][214] = 1;	errorCodeword[0][215] = 1;	errorCodeword[0][216] = 1;	errorCodeword[0][217] = 1;	errorCodeword[0][218] = 1;	errorCodeword[0][219] = 1;	errorCodeword[0][220] = 1;	errorCodeword[0][221] = 0;	errorCodeword[0][222] = 1;	errorCodeword[0][223] = 1;	errorCodeword[0][224] = 1;	errorCodeword[0][225] = 0;	errorCodeword[0][226] = 0;	errorCodeword[0][227] = 0;	errorCodeword[0][228] = 0;	errorCodeword[0][229] = 1;	errorCodeword[0][230] = 0;	errorCodeword[0][231] = 0;	errorCodeword[0][232] = 0;	errorCodeword[0][233] = 1;	errorCodeword[0][234] = 1;	errorCodeword[0][235] = 1;	errorCodeword[0][236] = 0;	errorCodeword[0][237] = 1;	errorCodeword[0][238] = 0;	errorCodeword[0][239] = 0;	errorCodeword[0][240] = 0;	errorCodeword[0][241] = 1;	errorCodeword[0][242] = 1;	errorCodeword[0][243] = 1;	errorCodeword[0][244] = 1;	errorCodeword[0][245] = 0;	errorCodeword[0][246] = 0;	errorCodeword[0][247] = 1;	errorCodeword[0][248] = 0;	errorCodeword[0][249] = 1;	errorCodeword[0][250] = 1;	errorCodeword[0][251] = 1;	errorCodeword[0][252] = 1;	errorCodeword[0][253] = 1;	errorCodeword[0][254] = 0;	errorCodeword[0][255] = 1;	errorCodeword[0][256] = 0;	errorCodeword[0][257] = 0;	errorCodeword[0][258] = 1;	errorCodeword[0][259] = 1;	errorCodeword[0][260] = 0;	errorCodeword[0][261] = 0;	errorCodeword[0][262] = 0;	errorCodeword[0][263] = 1;	errorCodeword[0][264] = 1;	errorCodeword[0][265] = 0;	errorCodeword[0][266] = 0;	errorCodeword[0][267] = 0;	errorCodeword[0][268] = 0;	errorCodeword[0][269] = 0;	errorCodeword[0][270] = 0;	errorCodeword[0][271] = 1;	errorCodeword[0][272] = 0;	errorCodeword[0][273] = 1;	errorCodeword[0][274] = 1;	errorCodeword[0][275] = 1;	errorCodeword[0][276] = 0;	errorCodeword[0][277] = 1;	errorCodeword[0][278] = 0;	errorCodeword[0][279] = 1;	errorCodeword[0][280] = 1;	errorCodeword[0][281] = 1;	errorCodeword[0][282] = 1;	errorCodeword[0][283] = 1;	errorCodeword[0][284] = 1;	errorCodeword[0][285] = 1;	errorCodeword[0][286] = 1;	errorCodeword[0][287] = 1;	errorCodeword[0][288] = 1;	errorCodeword[0][289] = 0;	errorCodeword[0][290] = 0;	errorCodeword[0][291] = 0;	errorCodeword[0][292] = 0;	errorCodeword[0][293] = 0;	errorCodeword[0][294] = 0;	errorCodeword[0][295] = 1;	errorCodeword[0][296] = 0;	errorCodeword[0][297] = 0;	errorCodeword[0][298] = 0;	errorCodeword[0][299] = 1;	errorCodeword[0][300] = 0;	errorCodeword[0][301] = 1;	errorCodeword[0][302] = 1;	errorCodeword[0][303] = 1;	errorCodeword[0][304] = 1;	errorCodeword[0][305] = 1;	errorCodeword[0][306] = 1;	errorCodeword[0][307] = 1;	errorCodeword[0][308] = 1;	errorCodeword[0][309] = 0;	errorCodeword[0][310] = 1;	errorCodeword[0][311] = 0;	errorCodeword[0][312] = 0;	errorCodeword[0][313] = 0;	errorCodeword[0][314] = 1;	errorCodeword[0][315] = 0;	errorCodeword[0][316] = 0;	errorCodeword[0][317] = 0;	errorCodeword[0][318] = 0;	errorCodeword[0][319] = 0;	errorCodeword[0][320] = 0;	errorCodeword[0][321] = 0;	errorCodeword[0][322] = 0;	errorCodeword[0][323] = 1;	errorCodeword[0][324] = 0;	errorCodeword[0][325] = 0;	errorCodeword[0][326] = 1;	errorCodeword[0][327] = 0;	errorCodeword[0][328] = 1;	errorCodeword[0][329] = 1;	errorCodeword[0][330] = 1;	errorCodeword[0][331] = 0;	errorCodeword[0][332] = 1;	errorCodeword[0][333] = 0;	errorCodeword[0][334] = 1;	errorCodeword[0][335] = 1;	errorCodeword[0][336] = 0;	errorCodeword[0][337] = 1;	errorCodeword[0][338] = 1;	errorCodeword[0][339] = 0;	errorCodeword[0][340] = 0;	errorCodeword[0][341] = 1;	errorCodeword[0][342] = 1;	errorCodeword[0][343] = 0;	errorCodeword[0][344] = 1;	errorCodeword[0][345] = 1;	errorCodeword[0][346] = 0;	errorCodeword[0][347] = 1;	errorCodeword[0][348] = 0;	errorCodeword[0][349] = 1;	errorCodeword[0][350] = 1;	errorCodeword[0][351] = 1;	errorCodeword[0][352] = 1;	errorCodeword[0][353] = 0;	errorCodeword[0][354] = 1;	errorCodeword[0][355] = 1;	errorCodeword[0][356] = 0;	errorCodeword[0][357] = 1;	errorCodeword[0][358] = 1;	errorCodeword[0][359] = 1;	errorCodeword[0][360] = 1;	errorCodeword[0][361] = 1;	errorCodeword[0][362] = 0;	errorCodeword[0][363] = 0;	errorCodeword[0][364] = 1;	errorCodeword[0][365] = 0;	errorCodeword[0][366] = 1;	errorCodeword[0][367] = 0;	errorCodeword[0][368] = 0;	errorCodeword[0][369] = 1;	errorCodeword[0][370] = 0;	errorCodeword[0][371] = 1;	errorCodeword[0][372] = 0;	errorCodeword[0][373] = 1;	errorCodeword[0][374] = 1;	errorCodeword[0][375] = 0;	errorCodeword[0][376] = 0;	errorCodeword[0][377] = 1;	errorCodeword[0][378] = 1;	errorCodeword[0][379] = 0;	errorCodeword[0][380] = 1;	errorCodeword[0][381] = 1;	errorCodeword[0][382] = 0;	errorCodeword[0][383] = 0;	errorCodeword[0][384] = 1;	errorCodeword[0][385] = 0;	errorCodeword[0][386] = 1;	errorCodeword[0][387] = 0;	errorCodeword[0][388] = 0;	errorCodeword[0][389] = 1;	errorCodeword[0][390] = 0;	errorCodeword[0][391] = 0;	errorCodeword[0][392] = 1;	errorCodeword[0][393] = 1;	errorCodeword[0][394] = 1;	errorCodeword[0][395] = 0;	errorCodeword[0][396] = 1;	errorCodeword[0][397] = 0;	errorCodeword[0][398] = 0;	errorCodeword[0][399] = 0;	errorCodeword[0][400] = 1;	errorCodeword[0][401] = 1;	errorCodeword[0][402] = 0;	errorCodeword[0][403] = 0;	errorCodeword[0][404] = 1;	errorCodeword[0][405] = 0;	errorCodeword[0][406] = 1;	errorCodeword[0][407] = 1;	errorCodeword[0][408] = 1;	errorCodeword[0][409] = 0;	errorCodeword[0][410] = 1;	errorCodeword[0][411] = 1;	errorCodeword[0][412] = 1;	errorCodeword[0][413] = 1;	errorCodeword[0][414] = 0;	errorCodeword[0][415] = 1;	errorCodeword[0][416] = 1;	errorCodeword[0][417] = 0;	errorCodeword[0][418] = 0;	errorCodeword[0][419] = 1;	errorCodeword[0][420] = 1;	errorCodeword[0][421] = 0;	errorCodeword[0][422] = 1;	errorCodeword[0][423] = 0;	errorCodeword[0][424] = 1;	errorCodeword[0][425] = 1;	errorCodeword[0][426] = 1;	errorCodeword[0][427] = 0;	errorCodeword[0][428] = 0;	errorCodeword[0][429] = 0;	errorCodeword[0][430] = 0;	errorCodeword[0][431] = 0;	errorCodeword[0][432] = 1;	errorCodeword[0][433] = 1;	errorCodeword[0][434] = 0;	errorCodeword[0][435] = 1;	errorCodeword[0][436] = 1;	errorCodeword[0][437] = 1;	errorCodeword[0][438] = 1;	errorCodeword[0][439] = 0;	errorCodeword[0][440] = 0;	errorCodeword[0][441] = 1;	errorCodeword[0][442] = 0;	errorCodeword[0][443] = 1;	errorCodeword[0][444] = 0;	errorCodeword[0][445] = 0;	errorCodeword[0][446] = 1;	errorCodeword[0][447] = 0;	errorCodeword[0][448] = 0;	errorCodeword[0][449] = 0;	errorCodeword[0][450] = 0;	errorCodeword[0][451] = 0;	errorCodeword[0][452] = 0;	errorCodeword[0][453] = 0;	errorCodeword[0][454] = 0;	errorCodeword[0][455] = 1;	errorCodeword[0][456] = 0;	errorCodeword[0][457] = 0;	errorCodeword[0][458] = 1;	errorCodeword[0][459] = 1;	errorCodeword[0][460] = 0;	errorCodeword[0][461] = 0;	errorCodeword[0][462] = 1;	errorCodeword[0][463] = 1;	errorCodeword[0][464] = 0;	errorCodeword[0][465] = 0;	errorCodeword[0][466] = 1;	errorCodeword[0][467] = 0;	errorCodeword[0][468] = 1;	errorCodeword[0][469] = 0;	errorCodeword[0][470] = 1;	errorCodeword[0][471] = 1;	errorCodeword[0][472] = 1;	errorCodeword[0][473] = 0;	errorCodeword[0][474] = 1;	errorCodeword[0][475] = 1;	errorCodeword[0][476] = 0;	errorCodeword[0][477] = 0;	errorCodeword[0][478] = 1;	errorCodeword[0][479] = 0;	errorCodeword[0][480] = 1;	errorCodeword[0][481] = 1;	errorCodeword[0][482] = 0;	errorCodeword[0][483] = 0;	errorCodeword[0][484] = 1;	errorCodeword[0][485] = 0;	errorCodeword[0][486] = 1;	errorCodeword[0][487] = 0;	errorCodeword[0][488] = 0;	errorCodeword[0][489] = 0;	errorCodeword[0][490] = 0;	errorCodeword[0][491] = 0;	errorCodeword[0][492] = 1;	errorCodeword[0][493] = 1;	errorCodeword[0][494] = 0;	errorCodeword[0][495] = 1;	errorCodeword[0][496] = 1;	errorCodeword[0][497] = 1;	errorCodeword[0][498] = 0;	errorCodeword[0][499] = 0;	errorCodeword[0][500] = 0;	errorCodeword[0][501] = 0;	errorCodeword[0][502] = 1;	errorCodeword[0][503] = 1;	errorCodeword[0][504] = 0;	errorCodeword[0][505] = 1;	errorCodeword[0][506] = 1;	errorCodeword[0][507] = 0;	errorCodeword[0][508] = 1;	errorCodeword[0][509] = 0;	errorCodeword[0][510] = 1;	errorCodeword[0][511] = 1;	errorCodeword[0][512] = 1;	errorCodeword[0][513] = 1;	errorCodeword[0][514] = 1;	errorCodeword[0][515] = 1;	errorCodeword[0][516] = 1;	errorCodeword[0][517] = 0;	errorCodeword[0][518] = 0;	errorCodeword[0][519] = 1;	errorCodeword[0][520] = 0;	errorCodeword[0][521] = 1;	errorCodeword[0][522] = 1;	errorCodeword[0][523] = 1;	errorCodeword[0][524] = 1;	errorCodeword[0][525] = 0;	errorCodeword[0][526] = 0;	errorCodeword[0][527] = 1;	errorCodeword[0][528] = 1;	errorCodeword[0][529] = 1;	errorCodeword[0][530] = 0;	errorCodeword[0][531] = 1;	errorCodeword[0][532] = 1;	errorCodeword[0][533] = 1;	errorCodeword[0][534] = 0;	errorCodeword[0][535] = 0;	errorCodeword[0][536] = 0;	errorCodeword[0][537] = 0;	errorCodeword[0][538] = 0;	errorCodeword[0][539] = 1;	errorCodeword[0][540] = 0;	errorCodeword[0][541] = 0;	errorCodeword[0][542] = 0;	errorCodeword[0][543] = 1;	errorCodeword[0][544] = 1;	errorCodeword[0][545] = 1;	errorCodeword[0][546] = 0;	errorCodeword[0][547] = 0;	errorCodeword[0][548] = 0;	errorCodeword[0][549] = 1;	errorCodeword[0][550] = 1;	errorCodeword[0][551] = 0;	errorCodeword[0][552] = 1;	errorCodeword[0][553] = 0;	errorCodeword[0][554] = 1;	errorCodeword[0][555] = 0;	errorCodeword[0][556] = 0;	errorCodeword[0][557] = 0;	errorCodeword[0][558] = 1;	errorCodeword[0][559] = 0;	errorCodeword[0][560] = 0;	errorCodeword[0][561] = 0;	errorCodeword[0][562] = 1;	errorCodeword[0][563] = 0;	errorCodeword[0][564] = 0;	errorCodeword[0][565] = 1;	errorCodeword[0][566] = 1;	errorCodeword[0][567] = 1;	errorCodeword[0][568] = 1;	errorCodeword[0][569] = 0;	errorCodeword[0][570] = 1;	errorCodeword[0][571] = 0;	errorCodeword[0][572] = 1;	errorCodeword[0][573] = 1;	errorCodeword[0][574] = 1;	errorCodeword[0][575] = 0;	errorCodeword[0][576] = 0;	errorCodeword[0][577] = 1;	errorCodeword[0][578] = 0;	errorCodeword[0][579] = 1;	errorCodeword[0][580] = 0;	errorCodeword[0][581] = 1;	errorCodeword[0][582] = 1;	errorCodeword[0][583] = 0;	errorCodeword[0][584] = 0;	errorCodeword[0][585] = 0;	errorCodeword[0][586] = 0;	errorCodeword[0][587] = 0;	errorCodeword[0][588] = 1;	errorCodeword[0][589] = 1;	errorCodeword[0][590] = 0;	errorCodeword[0][591] = 0;	errorCodeword[0][592] = 0;	errorCodeword[0][593] = 0;	errorCodeword[0][594] = 0;	errorCodeword[0][595] = 1;	errorCodeword[0][596] = 1;	errorCodeword[0][597] = 0;	errorCodeword[0][598] = 0;	errorCodeword[0][599] = 1;	errorCodeword[0][600] = 1;	errorCodeword[0][601] = 1;	errorCodeword[0][602] = 0;	errorCodeword[0][603] = 0;	errorCodeword[0][604] = 0;	errorCodeword[0][605] = 0;	errorCodeword[0][606] = 1;	errorCodeword[0][607] = 1;	errorCodeword[0][608] = 0;	errorCodeword[0][609] = 0;	errorCodeword[0][610] = 0;	errorCodeword[0][611] = 1;	errorCodeword[0][612] = 1;	errorCodeword[0][613] = 1;	errorCodeword[0][614] = 1;	errorCodeword[0][615] = 0;	errorCodeword[0][616] = 0;	errorCodeword[0][617] = 0;	errorCodeword[0][618] = 1;	errorCodeword[0][619] = 1;	errorCodeword[0][620] = 0;	errorCodeword[0][621] = 1;	errorCodeword[0][622] = 1;	errorCodeword[0][623] = 1;	errorCodeword[0][624] = 1;	errorCodeword[0][625] = 0;	errorCodeword[0][626] = 1;	errorCodeword[0][627] = 0;	errorCodeword[0][628] = 1;	errorCodeword[0][629] = 1;	errorCodeword[0][630] = 0;	errorCodeword[0][631] = 1;	errorCodeword[0][632] = 1;	errorCodeword[0][633] = 1;	errorCodeword[0][634] = 0;	errorCodeword[0][635] = 1;	errorCodeword[0][636] = 1;	errorCodeword[0][637] = 1;	errorCodeword[0][638] = 1;	errorCodeword[0][639] = 0;	errorCodeword[0][640] = 1;	errorCodeword[0][641] = 0;	errorCodeword[0][642] = 1;	errorCodeword[0][643] = 0;	errorCodeword[0][644] = 0;	errorCodeword[0][645] = 1;	errorCodeword[0][646] = 0;	errorCodeword[0][647] = 0;	errorCodeword[0][648] = 0;	errorCodeword[0][649] = 0;	errorCodeword[0][650] = 0;	errorCodeword[0][651] = 0;	errorCodeword[0][652] = 0;	errorCodeword[0][653] = 0;	errorCodeword[0][654] = 0;	errorCodeword[0][655] = 1;	errorCodeword[0][656] = 0;	errorCodeword[0][657] = 1;	errorCodeword[0][658] = 1;	errorCodeword[0][659] = 0;	errorCodeword[0][660] = 1;	errorCodeword[0][661] = 1;	errorCodeword[0][662] = 0;	errorCodeword[0][663] = 1;	errorCodeword[0][664] = 1;	errorCodeword[0][665] = 1;	errorCodeword[0][666] = 0;	errorCodeword[0][667] = 0;	errorCodeword[0][668] = 0;	errorCodeword[0][669] = 1;	errorCodeword[0][670] = 0;	errorCodeword[0][671] = 1;	errorCodeword[0][672] = 1;	errorCodeword[0][673] = 1;	errorCodeword[0][674] = 0;	errorCodeword[0][675] = 0;	errorCodeword[0][676] = 0;	errorCodeword[0][677] = 1;	errorCodeword[0][678] = 1;	errorCodeword[0][679] = 0;	errorCodeword[0][680] = 1;	errorCodeword[0][681] = 0;	errorCodeword[0][682] = 0;	errorCodeword[0][683] = 1;	errorCodeword[0][684] = 0;	errorCodeword[0][685] = 0;	errorCodeword[0][686] = 1;	errorCodeword[0][687] = 0;	errorCodeword[0][688] = 1;	errorCodeword[0][689] = 0;	errorCodeword[0][690] = 1;	errorCodeword[0][691] = 1;	errorCodeword[0][692] = 0;	errorCodeword[0][693] = 0;	errorCodeword[0][694] = 1;	errorCodeword[0][695] = 0;	errorCodeword[0][696] = 1;	errorCodeword[0][697] = 1;	errorCodeword[0][698] = 0;	errorCodeword[0][699] = 1;	errorCodeword[0][700] = 1;	errorCodeword[0][701] = 1;	errorCodeword[0][702] = 0;	errorCodeword[0][703] = 0;	errorCodeword[0][704] = 1;	errorCodeword[0][705] = 1;	errorCodeword[0][706] = 0;	errorCodeword[0][707] = 0;	errorCodeword[0][708] = 0;	errorCodeword[0][709] = 1;	errorCodeword[0][710] = 1;	errorCodeword[0][711] = 1;	errorCodeword[0][712] = 1;	errorCodeword[0][713] = 1;	errorCodeword[0][714] = 1;	errorCodeword[0][715] = 1;	errorCodeword[0][716] = 1;	errorCodeword[0][717] = 0;	errorCodeword[0][718] = 1;	errorCodeword[0][719] = 1;	errorCodeword[0][720] = 0;	errorCodeword[0][721] = 0;	errorCodeword[0][722] = 0;	errorCodeword[0][723] = 1;	errorCodeword[0][724] = 1;	errorCodeword[0][725] = 0;	errorCodeword[0][726] = 0;	errorCodeword[0][727] = 1;	errorCodeword[0][728] = 0;	errorCodeword[0][729] = 1;	errorCodeword[0][730] = 1;	errorCodeword[0][731] = 0;	errorCodeword[0][732] = 1;	errorCodeword[0][733] = 0;	errorCodeword[0][734] = 1;	errorCodeword[0][735] = 0;	errorCodeword[0][736] = 0;	errorCodeword[0][737] = 1;	errorCodeword[0][738] = 1;	errorCodeword[0][739] = 0;	errorCodeword[0][740] = 0;	errorCodeword[0][741] = 0;	errorCodeword[0][742] = 1;	errorCodeword[0][743] = 1;	errorCodeword[0][744] = 0;	errorCodeword[0][745] = 1;	errorCodeword[0][746] = 0;	errorCodeword[0][747] = 0;	errorCodeword[0][748] = 1;	errorCodeword[0][749] = 0;	errorCodeword[0][750] = 0;	errorCodeword[0][751] = 1;	errorCodeword[0][752] = 1;	errorCodeword[0][753] = 1;	errorCodeword[0][754] = 1;	errorCodeword[0][755] = 1;	errorCodeword[0][756] = 1;	errorCodeword[0][757] = 1;	errorCodeword[0][758] = 1;	errorCodeword[0][759] = 1;	errorCodeword[0][760] = 1;	errorCodeword[0][761] = 0;	errorCodeword[0][762] = 0;	errorCodeword[0][763] = 0;	errorCodeword[0][764] = 1;	errorCodeword[0][765] = 0;	errorCodeword[0][766] = 0;	errorCodeword[0][767] = 1;	errorCodeword[0][768] = 1;	errorCodeword[0][769] = 0;	errorCodeword[0][770] = 1;	errorCodeword[0][771] = 1;	errorCodeword[0][772] = 1;	errorCodeword[0][773] = 0;	errorCodeword[0][774] = 1;	errorCodeword[0][775] = 1;	errorCodeword[0][776] = 1;	errorCodeword[0][777] = 0;	errorCodeword[0][778] = 0;	errorCodeword[0][779] = 0;	errorCodeword[0][780] = 1;	errorCodeword[0][781] = 0;	errorCodeword[0][782] = 0;	errorCodeword[0][783] = 1;	errorCodeword[0][784] = 0;	errorCodeword[0][785] = 1;	errorCodeword[0][786] = 1;	errorCodeword[0][787] = 0;	errorCodeword[0][788] = 0;	errorCodeword[0][789] = 0;	errorCodeword[0][790] = 1;	errorCodeword[0][791] = 0;	errorCodeword[0][792] = 1;	errorCodeword[0][793] = 1;	errorCodeword[0][794] = 0;	errorCodeword[0][795] = 0;	errorCodeword[0][796] = 0;	errorCodeword[0][797] = 0;	errorCodeword[0][798] = 0;	errorCodeword[0][799] = 1;	errorCodeword[0][800] = 0;	errorCodeword[0][801] = 0;	errorCodeword[0][802] = 0;	errorCodeword[0][803] = 0;	errorCodeword[0][804] = 1;	errorCodeword[0][805] = 0;	errorCodeword[0][806] = 1;	errorCodeword[0][807] = 0;	errorCodeword[0][808] = 0;	errorCodeword[0][809] = 1;	errorCodeword[0][810] = 1;	errorCodeword[0][811] = 1;	errorCodeword[0][812] = 0;	errorCodeword[0][813] = 0;	errorCodeword[0][814] = 0;	errorCodeword[0][815] = 1;	errorCodeword[0][816] = 0;	errorCodeword[0][817] = 1;	errorCodeword[0][818] = 1;	errorCodeword[0][819] = 1;	errorCodeword[0][820] = 1;	errorCodeword[0][821] = 0;	errorCodeword[0][822] = 0;	errorCodeword[0][823] = 1;	errorCodeword[0][824] = 0;	errorCodeword[0][825] = 0;	errorCodeword[0][826] = 1;	errorCodeword[0][827] = 0;	errorCodeword[0][828] = 0;	errorCodeword[0][829] = 0;	errorCodeword[0][830] = 0;	errorCodeword[0][831] = 1;	errorCodeword[0][832] = 1;	errorCodeword[0][833] = 0;	errorCodeword[0][834] = 1;	errorCodeword[0][835] = 0;	errorCodeword[0][836] = 1;	errorCodeword[0][837] = 1;	errorCodeword[0][838] = 0;	errorCodeword[0][839] = 1;	errorCodeword[0][840] = 1;	errorCodeword[0][841] = 1;	errorCodeword[0][842] = 1;	errorCodeword[0][843] = 1;	errorCodeword[0][844] = 0;	errorCodeword[0][845] = 1;	errorCodeword[0][846] = 1;	errorCodeword[0][847] = 1;	errorCodeword[0][848] = 0;	errorCodeword[0][849] = 0;	errorCodeword[0][850] = 0;	errorCodeword[0][851] = 1;	errorCodeword[0][852] = 0;	errorCodeword[0][853] = 0;	errorCodeword[0][854] = 1;	errorCodeword[0][855] = 0;	errorCodeword[0][856] = 0;	errorCodeword[0][857] = 0;	errorCodeword[0][858] = 1;	errorCodeword[0][859] = 0;	errorCodeword[0][860] = 1;	errorCodeword[0][861] = 1;	errorCodeword[0][862] = 1;	errorCodeword[0][863] = 0;	errorCodeword[0][864] = 1;	errorCodeword[0][865] = 0;	errorCodeword[0][866] = 1;	errorCodeword[0][867] = 1;	errorCodeword[0][868] = 1;	errorCodeword[0][869] = 1;	errorCodeword[0][870] = 0;	errorCodeword[0][871] = 0;	errorCodeword[0][872] = 1;	errorCodeword[0][873] = 0;	errorCodeword[0][874] = 0;	errorCodeword[0][875] = 1;	errorCodeword[0][876] = 0;	errorCodeword[0][877] = 0;	errorCodeword[0][878] = 1;	errorCodeword[0][879] = 1;	errorCodeword[0][880] = 1;	errorCodeword[0][881] = 0;	errorCodeword[0][882] = 0;	errorCodeword[0][883] = 0;	errorCodeword[0][884] = 1;	errorCodeword[0][885] = 0;	errorCodeword[0][886] = 0;	errorCodeword[0][887] = 0;	errorCodeword[0][888] = 1;	errorCodeword[0][889] = 1;	errorCodeword[0][890] = 0;	errorCodeword[0][891] = 0;	errorCodeword[0][892] = 1;	errorCodeword[0][893] = 0;	errorCodeword[0][894] = 1;	errorCodeword[0][895] = 0;	errorCodeword[0][896] = 0;	errorCodeword[0][897] = 0;	errorCodeword[0][898] = 0;	errorCodeword[0][899] = 0;	errorCodeword[0][900] = 1;	errorCodeword[0][901] = 0;	errorCodeword[0][902] = 1;	errorCodeword[0][903] = 0;	errorCodeword[0][904] = 0;	errorCodeword[0][905] = 1;	errorCodeword[0][906] = 1;	errorCodeword[0][907] = 0;	errorCodeword[0][908] = 1;	errorCodeword[0][909] = 1;	errorCodeword[0][910] = 1;	errorCodeword[0][911] = 0;	errorCodeword[0][912] = 0;	errorCodeword[0][913] = 0;	errorCodeword[0][914] = 0;	errorCodeword[0][915] = 0;	errorCodeword[0][916] = 0;	errorCodeword[0][917] = 1;	errorCodeword[0][918] = 1;	errorCodeword[0][919] = 0;	errorCodeword[0][920] = 0;	errorCodeword[0][921] = 0;	errorCodeword[0][922] = 0;	errorCodeword[0][923] = 0;	errorCodeword[0][924] = 1;	errorCodeword[0][925] = 1;	errorCodeword[0][926] = 0;	errorCodeword[0][927] = 1;	errorCodeword[0][928] = 1;	errorCodeword[0][929] = 0;	errorCodeword[0][930] = 0;	errorCodeword[0][931] = 1;	errorCodeword[0][932] = 0;	errorCodeword[0][933] = 0;	errorCodeword[0][934] = 1;	errorCodeword[0][935] = 0;	errorCodeword[0][936] = 0;	errorCodeword[0][937] = 1;	errorCodeword[0][938] = 1;	errorCodeword[0][939] = 0;	errorCodeword[0][940] = 1;	errorCodeword[0][941] = 0;	errorCodeword[0][942] = 1;	errorCodeword[0][943] = 0;	errorCodeword[0][944] = 0;	errorCodeword[0][945] = 0;	errorCodeword[0][946] = 0;	errorCodeword[0][947] = 1;	errorCodeword[0][948] = 1;	errorCodeword[0][949] = 1;	errorCodeword[0][950] = 1;	errorCodeword[0][951] = 1;	errorCodeword[0][952] = 0;	errorCodeword[0][953] = 1;	errorCodeword[0][954] = 0;	errorCodeword[0][955] = 0;	errorCodeword[0][956] = 0;	errorCodeword[0][957] = 1;	errorCodeword[0][958] = 0;	errorCodeword[0][959] = 0;	errorCodeword[0][960] = 1;	errorCodeword[0][961] = 1;	errorCodeword[0][962] = 1;	errorCodeword[0][963] = 0;	errorCodeword[0][964] = 1;	errorCodeword[0][965] = 1;	errorCodeword[0][966] = 1;	errorCodeword[0][967] = 0;	errorCodeword[0][968] = 0;	errorCodeword[0][969] = 1;	errorCodeword[0][970] = 0;	errorCodeword[0][971] = 1;	errorCodeword[0][972] = 0;	errorCodeword[0][973] = 0;	errorCodeword[0][974] = 0;	errorCodeword[0][975] = 1;	errorCodeword[0][976] = 0;	errorCodeword[0][977] = 1;	errorCodeword[0][978] = 1;	errorCodeword[0][979] = 0;	errorCodeword[0][980] = 1;	errorCodeword[0][981] = 1;	errorCodeword[0][982] = 0;	errorCodeword[0][983] = 0;	errorCodeword[0][984] = 0;	errorCodeword[0][985] = 0;	errorCodeword[0][986] = 1;	errorCodeword[0][987] = 0;	errorCodeword[0][988] = 0;	errorCodeword[0][989] = 1;	errorCodeword[0][990] = 0;	errorCodeword[0][991] = 1;	errorCodeword[0][992] = 1;	errorCodeword[0][993] = 0;	errorCodeword[0][994] = 0;	errorCodeword[0][995] = 0;	errorCodeword[0][996] = 1;	errorCodeword[0][997] = 1;	errorCodeword[0][998] = 0;	errorCodeword[0][999] = 0;	errorCodeword[0][1000] = 1;	errorCodeword[0][1001] = 0;	errorCodeword[0][1002] = 0;	errorCodeword[0][1003] = 1;	errorCodeword[0][1004] = 0;	errorCodeword[0][1005] = 0;	errorCodeword[0][1006] = 1;	errorCodeword[0][1007] = 1;	errorCodeword[0][1008] = 0;	errorCodeword[0][1009] = 1;	errorCodeword[0][1010] = 1;	errorCodeword[0][1011] = 1;	errorCodeword[0][1012] = 0;	errorCodeword[0][1013] = 0;	errorCodeword[0][1014] = 0;	errorCodeword[0][1015] = 0;	errorCodeword[0][1016] = 0;	errorCodeword[0][1017] = 1;	errorCodeword[0][1018] = 0;	errorCodeword[0][1019] = 1;	errorCodeword[0][1020] = 0;	errorCodeword[0][1021] = 1;	errorCodeword[0][1022] = 0;	errorCodeword[0][1023] = 1;

	rmDecoder(r, m, G, n, errorCodeword, recovery);
	
	/*printf("recovery : \n");
	for (int i = 0; i < k; i++)
	{
		printf("%d ", recovery[0][i]);
	}
	printf("\n"); printf("\n");*/


	for (int i = 0; i < k; i++)
	{
		if (msg[0][i] != recovery[0][i])
		{
			printf("error msg[%d] : %d\n", test, i);
			break;
		}
	}


	free(codeword[0]);
	free(codeword);


	free(errorCodeword[0]);
	free(errorCodeword);
	
	free(recovery[0]);
	free(recovery);

	free(msg[0]);
	free(msg);
	
}


	for (int i = 0; i < k; i++)
	{
		free(G[i]);
	}

	free(G);

	return;
}



void rmIdxCalculator(unsigned short *array, const short& arrayLen, unsigned short& arrayPointer, unsigned short *result, unsigned short& resultIdx, unsigned short& resultValue)
{
	if (arrayLen == arrayPointer)
	{
		arrayPointer--;

		result[resultIdx] = resultValue;
		resultIdx++;

		return;
	}

	for (int i = 0; i < 2; i++)
	{
		unsigned short temp = power(array[arrayPointer]) * i;
		resultValue += temp;

		arrayPointer++;
		rmIdxCalculator(array, arrayLen, arrayPointer, result, resultIdx, resultValue);

		resultValue -= temp;
	}
	arrayPointer--;
}


void rmSCalculate(unsigned short *row, const short& rowLength, unsigned short *S)
{
	unsigned short *rowCopy = (unsigned short *)malloc(sizeof(unsigned short) * rowLength);

	for (int i = 0; i < rowLength; i++)
	{
		rowCopy[i] = row[i] - 1;
	}

	unsigned short SValue = 0;
	unsigned short SIdx = 0;

	unsigned short rowPointer = 0;

	rmIdxCalculator(rowCopy, rowLength, rowPointer, S, SIdx, SValue);

	free(rowCopy);

}

void rmECalculate(unsigned short *row, const short& rowLength, const short& m, unsigned short *E)
{

	int k = 0;
	for (int i = 0; i < m; i++)
	{
		int temp = 0;
		for (int j = 0; j < rowLength; j++)
		{
			if (i == (row[j] - 1))
			{
				temp = 1;
				break;
			}
		}

		if (temp == 0)
		{
			E[k] = i;
			k++;
		}
	}
}

void rmSCCalculate(unsigned short *row, const short& rowLength, unsigned short *SC)
{
	unsigned short SCValue = 0;
	unsigned short SCIdx = 0;

	unsigned short rowPointer = 0;

	rmIdxCalculator(row, rowLength, rowPointer, SC, SCIdx, SCValue);
}

unsigned char rmDecision(unsigned short *array, unsigned short arrayLength)
{
	short zeroCount = 0;
	short oneCount = 0;

	for (int i = 0; i < arrayLength; i++)
	{
		//printf("%d ", array[i]);
		if (0 == array[i])
		{
			zeroCount++;
		}
		else
		{
			oneCount++;
		}
		
	}

	if (zeroCount > oneCount)
		return 0;
	else if (zeroCount < oneCount)
		return 1;
	else
		return rand() % 2;
}

unsigned char rmACalculate(unsigned short& SLength, unsigned short *S, const unsigned short& SCLength, unsigned short *SC, unsigned char **codeword)
{
	unsigned short *A = (unsigned short *)malloc(sizeof(unsigned short) * SCLength);

	unsigned char val;
	for (int i = 0; i < SCLength; i++)
	{
		short sum = 0;

		for (int j = 0; j < SLength; j++)
		{
			sum += codeword[0][S[j] + SC[i]];
		}
		A[i] = sum % 2;
	}

	val = rmDecision(A, SCLength);

	free(A);

	return val;
}


void rmDecoding(const short& n, const short& m, const short& rowLength, unsigned short* row, short rowIdx, short& rowValue, unsigned char **codeword, unsigned char **recovery, unsigned short& recoveryIdx)
{
	if (rowLength <= rowIdx)
	{
		/*int i = 0;
		printf("%d : ", recoveryIdx);
		while (i != rowIdx)
		{
		printf("%d ", row[i]);
		i++;
		}
		printf("\n");*/



		/**/
		unsigned short SLength = power(rowLength);
		unsigned short *S = (unsigned short *)malloc(sizeof(unsigned short) * SLength);
		rmSCalculate(row, rowLength, S);

		/*for (int i = 0; i < SLength; i++)
		{
		printf("%d ", S[i]);
		}
		printf("\n");*/

		unsigned short ELength = m - (rowLength);
		unsigned short *E = (unsigned short *)malloc(sizeof(unsigned short) * ELength);
		rmECalculate(row, rowLength, m, E);

		unsigned short SCLength = power(ELength);
		unsigned short *SC = (unsigned short *)malloc(sizeof(unsigned short) * SCLength);
		rmSCCalculate(E, ELength, SC);

		/*for (int i = 0; i < SCLength; i++)
		{
		printf("%d ", SC[i]);
		}
		printf("\n");*/

		recovery[0][recoveryIdx] = rmACalculate(SLength, S, SCLength, SC, codeword);
		//printf("%d ", recovery[0][recoveryIdx]);

		free(SC);
		free(E);
		free(S);
		/**/

		recoveryIdx++;
		//printf("\n");
		return;
	}

	for (short i = rowValue - 1; i >= 1; i--)
	{
		row[rowIdx] = i;
		rmDecoding(n, m, rowLength, row, rowIdx + 1, i, codeword, recovery, recoveryIdx);
	}

}

void rmRUpdate(unsigned short& start, unsigned short& end, unsigned char **recovery, unsigned char **G, unsigned char **codeword, const unsigned short& n)
{
	for (int i = 0; i < n; i++)
	{
		unsigned char sum = 0;
		for (int j = start; j < end; j++)
		{
			//printf("%d * %d = %d\n", recovery[0][j], G[j][i], recovery[0][j] * G[j][i]);
			sum += (recovery[0][j] * G[j][i]);
		}
		//printf("%d\n", (codeword[0][i] + sum) % 2);
		codeword[0][i] = (codeword[0][i] + sum) % 2;
	}
}

void rmDecoder(const unsigned short& r, const unsigned short& m, unsigned char **GRM, const unsigned short& n, unsigned char **codeword, unsigned char **recovery)
{
	unsigned short* multiplRows = (unsigned short*)malloc(sizeof(unsigned short) * r);

	for (unsigned short i = r; i >= 1; i--)
	{
		static unsigned short recoveryIdx = m + 1;
		static unsigned short upIdx = recoveryIdx;

		for (short j = m; j >= 1; j--)
		{
			short rowIdx = 0;
			if (i == 1)
			{
				recoveryIdx = j;
			}

			multiplRows[rowIdx] = j;
			rmDecoding(n, m, i, multiplRows, rowIdx + 1, j, codeword, recovery, recoveryIdx);
		}


		if (i == 1)
		{
			upIdx = 1;
			recoveryIdx = m + 1;
		}
		
		rmRUpdate(upIdx, recoveryIdx, recovery, GRM, codeword, n);
		
		upIdx = recoveryIdx;
	}

	unsigned short *one = (unsigned short *)malloc(sizeof(unsigned short) * n);
	
	for (short j = 0; j < n; j++)
	{
		one[j] = codeword[0][j];
	}

	recovery[0][0] = rmDecision(one, n);

	free(one);
	free(multiplRows);
}

void rmEncoder(const unsigned short k, unsigned char **msg, const unsigned short n, unsigned char **G, unsigned char **codeword)
{
	mtrixMultiplication(1, k, msg, k, n, G, codeword);
}







unsigned short power(const unsigned short& exponent)
{
	return (1 << exponent);
}

unsigned short combination(unsigned short n, const unsigned short& k)
{
	if (k > n) return 0;

	unsigned short result = 1;
	for (unsigned short i = 1; i <= k; i++)
	{
		result *= n--;
		result /= i;
	}

	return result;
}

void mtrixMultiplication(const unsigned int& pRow, const unsigned int& pCol, unsigned char** prev, const unsigned int& nRow, const unsigned int& nCol, unsigned char** next, unsigned char** result)
{
	for (int i = 0; i < pRow; i++)
	{
		for (int j = 0; j < nCol; j++)
		{
			unsigned char sum = 0;
			for (int z = 0; z < pCol; z++)
			{
				sum ^= (prev[i][z] * next[z][j]);
			}
			result[i][j] = sum;
		}
	}
}

void errorGenerator(const unsigned int& weight, const unsigned int& size, unsigned char* error)
{
	srand((unsigned)time(NULL));

	int num = 0;

	while (1)
	{
		unsigned int idx = rand() % size;

		if (error[idx] == 0)
		{
			error[idx] = 1;
			num++;
		}

		if (num >= weight)
		{
			break;
		}
	}
}

void errorAdd(const unsigned int& size, unsigned char* original, unsigned char* error, unsigned char* result)
{
	for (int i = 0; i < size; i++)
	{
		result[i] = original[i];

		if (error[i] == 1)
		{
			if (original[i] == 0)
			{
				result[i] = 1;
			}
			else
			{
				result[i] = 0;
			}
			//result[i] = (~original[i])%2;
		}
	}

}

void grm(const short& n, const short& m, const short& lim, unsigned char** matrix, unsigned short& idx, short *row, short rowIdx, short& rowValue)
{
	if (lim <= rowIdx)
	{
		int i = 0;
		//printf("%d : ", idx);
		while (i != rowIdx)
		{
			//printf("%d ", row[i]);
			for (int j = 0; j < n; j++)
			{
				matrix[idx][j] *= matrix[row[i]][j];
			}
			i++;
		}
		idx++;
		//printf("\n");
		return;
	}

	for (short i = rowValue - 1; i >= 1; i--)
	{
		row[rowIdx] = i;
		grm(n, m, lim, matrix, idx, row, rowIdx + 1, i);
	}

}

void generateMatrix(const short& r, const short& m, const short& n, unsigned char **matrix)
{
	for (int i = 0; i < n; i++)
	{
		matrix[0][i] = 1;
	}

	for (int i = 1; i <= m; i++)
	{
		static unsigned char temp = 0;
		int z = 0;
		for (int j = 0; j < n / power(i - 1); j++)
		{
			for (int k = 0; k < power(i - 1); k++)
			{
				matrix[i][z] = temp;
				z++;
			}
			temp = temp == 0 ? 1 : 0;
		}
	}


	for (int i = r; i > 1; i--)
	{
		short* multiplRows = (short*)malloc(sizeof(short) * r);
		for (short j = m; j >= 1; j--)
		{
			short rowIdx = 0;
			static unsigned short idx = m + 1;
			multiplRows[rowIdx] = j;
			grm(n, m, i, matrix, idx, multiplRows, rowIdx + 1, j);
		}
		free(multiplRows);
	}


	/*for(int i = 2; i <= r; i++)
	{
	short* multiplRows = (short*)malloc(sizeof(int) * r);
	for (int j = 1; j <= m; j++)
	{
	int rowIdx = 0;
	static unsigned short idx = m + 1;
	multiplRows[rowIdx] = j;
	grm(n, m, i, matrix, idx, multiplRows, rowIdx + 1, j);
	}
	free(multiplRows);
	}*/

}


void rcsvDecisionZero(double *orgMsg, int orgMsgLength, double *result, int resultLength)
{
	double sum = 0;
	for (int i = 0; i<resultLength; i++)
		sum += orgMsg[i];

	double everage = sum / orgMsgLength;
	for (int i = 0; i<resultLength; i++)
	{
		if (everage > 0)
			result[i] = 1;
		else if (everage < 0)
			result[i] = -1;
		else
			result[i] = (rand() % 2) == 0 ? 1 : -1;
	}
}

void rcsvDecisionEqual(double *orgMsg, int orgMsgLength, double *result, int resultLength)
{
	for (int i = 0; i<resultLength; i++)
	{
		if (orgMsg[i] > 0)
			result[i] = 1;
		else if (orgMsg[i] < 0)
			result[i] = -1;
		else
			result[i] = (rand() % 2) == 0 ? 1 : -1;
	}
}
double *rcsvLeft(int r, int m, double *orgMsg, int orgMsgLength, double *v, int vLength, double *result, int resultLength)
{
	double *yu;
	int yuLength = resultLength;

	yu = (double *)malloc(sizeof(double) * yuLength);

	for (int i = 0; i<yuLength; i++)
	{
		yu[i] = (orgMsg[i] + (orgMsg[i + yuLength] * v[i])) / 2;
	}

	result = (double *)malloc(sizeof(double) * resultLength);
	if (r == 0)
	{
		rcsvDecisionZero(yu, yuLength, result, resultLength);
	}
	else if (r == m)
	{
		rcsvDecisionEqual(yu, yuLength, result, resultLength);
	}
	else
	{
		double *v = NULL;
		int vLength = yuLength / 2;

		double *u = NULL;
		int uLength = yuLength / 2;

		v = rcsvRight(r - 1, m - 1, yu, yuLength, v, vLength);
		u = rcsvLeft(r, m - 1, yu, yuLength, v, vLength, u, uLength);

		for (int i = 0; i<uLength; i++)
		{
			result[i + uLength] = u[i] * v[i];
			result[i] = u[i];
		}

		free(v);
		free(u);
	}

	free(yu);

	return result;
}

double *rcsvRight(int r, int m, double *orgMsg, int orgMsgLength, double *result, int resultLength)
{
	double *yv;
	int yvLength = resultLength;

	yv = (double *)malloc(sizeof(double) * yvLength);
	for (int i = 0; i<yvLength; i++)
	{
		yv[i] = orgMsg[i] * orgMsg[i + yvLength];
	}

	result = (double *)malloc(sizeof(double) * resultLength);
	if (r == 0)
	{
		rcsvDecisionZero(yv, yvLength, result, resultLength);
	}
	else if (r == m)
	{
		rcsvDecisionEqual(yv, yvLength, result, resultLength);
	}
	else
	{
		double *v = NULL;
		int vLength = yvLength / 2;

		double *u = NULL;
		int uLength = yvLength / 2;

		v = rcsvRight(r - 1, m - 1, yv, yvLength, v, vLength);
		u = rcsvLeft(r, m - 1, yv, yvLength, v, vLength, u, uLength);

		for (int i = 0; i<uLength; i++)
		{
			result[i + (uLength)] = u[i] * v[i];
			result[i] = u[i];
		}

		free(v);
		free(u);
	}

	free(yv);

	return result;
}




void rcsvDecodingHard(int r, int m, unsigned char *recvCodeword, int recvCodewordLength)
{
	double *codeword;
	int codewordLength = power(m);
	codeword = (double *)malloc(sizeof(double) * codewordLength);

	double *result;
	result = (double *)malloc(sizeof(double) * power(m));

	for (int i = 0; i<recvCodewordLength; i++)
	{
		if (recvCodeword[i] == 1)
			codeword[i] = -1;
		else
			codeword[i] = 1;
	}

	double *v = NULL;
	int vLength = codewordLength / 2;
	double *u = NULL;
	int uLength = codewordLength / 2;

	v = rcsvRight(r - 1, m - 1, codeword, codewordLength, v, vLength);
	u = rcsvLeft(r, m - 1, codeword, codewordLength, v, vLength, u, uLength);

	for (int i = 0; i<uLength; i++)
	{
		result[i + uLength] = u[i] * v[i];
		result[i] = u[i];
	}

	for (int i = 0; i<recvCodewordLength; i++)
	{
		if (result[i] == -1)
		{
			recvCodeword[i] = 1;
		}
		else
		{
			recvCodeword[i] = 0;
		}
	}

	free(v);
	free(u);

	free(result);
	free(codeword);
}