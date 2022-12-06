//********************************************
// Student Name			:������
// Student ID			:109550136
// Student Email Address:james61124@gmail.com
//********************************************
//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2021/04/
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
	flg_AutoPlay = false;
	mNX = nx;
    mNZ = nz;
    reset();
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //
	mNX = nx;
    mNZ = nz;
    reset();
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious( const BASE_SYSTEM *m )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[j][i] = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = 0;
            mPreviousBoard[i][j] = 0;
        }
    }
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "a or A: To automatically play for one step." << endl;
    cout << "r: clear all the cells" << endl << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
	vector<int> vec;
    int newn = (rand() % 2 + 1) * 2; // generate 2 4
    for (int j = mNZ - 1; j >= 0; j--) {
        for (int i = 0; i < mNX; i++) {
            if (!mBoard[j][i]) //�YmBoard��0(��Ŧ�)
                vec.push_back(i);//�N�N�Ŧ�s��vec
        }
        if (vec.size()) {//�Yvec�̭����F��N�i�J(��ܳo�C���a��O�Ū�)
            mBoard[j][vec[rand() % (vec.size())]] = newn; //�u�b���Ŧ쪺�̤W�����ƥX�{�Ʀr ����O�H�� �M��break�X�h
            break;
        }
    }
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //    
	int block, curFilledBLock;
    for (int i = 0; i < mNX; i++) {
        block = 0, curFilledBLock = 0;
        for (int j = 0; j < mNZ; j++) { //�ѤU���W
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[curFilledBLock][i] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[curFilledBLock][i] = block * 2;
                curFilledBLock++;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[curFilledBLock][i] = block;
                block = mBoard[j][i];
                curFilledBLock++;
            }

        }
        if (block)
            mBoard[curFilledBLock++][i] = block;
        while (curFilledBLock < mNZ)
            mBoard[curFilledBLock++][i] = 0;
    }

}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int i = mNX - 1; i >= 0; i--) {
        block = 0, curFilledBLock = mNX - 1;//curFilledBlock�s�ثe�W�b�����F��O��ĴX�� ��0�����F�� curFilledBlock=1
        for (int j = mNZ - 1; j >= 0; j--) {//�ѤW���U��
            mPreviousBoard[j][i] = mBoard[j][i]; //���ƻs�s��Board���ª�Board
            if (!block) //�Yblock��0
                block = mBoard[j][i];//�N�ƻsmBoard��block��
            else if (block == mBoard[j][i]) { //�Yblock�MmBoard�@��(�N�[�_��)
                if (block * 2 == 4096)
                {
                    mBoard[curFilledBLock][i] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[curFilledBLock][i] = block * 2;// ���ثe���F�誺�o����block(�Ȧs���W�@��Ʀr)�[�_��
                curFilledBLock--;//���F�誺��l�N�|�]��o��
                block = 0;
            }
            else if (0 != mBoard[j][i]) { //�YmBoard���O�Ū�,�ӥB�Mblock���@��
                mBoard[curFilledBLock][i] = block;//
                block = mBoard[j][i];
                curFilledBLock--;
            }

        }
        if (block) //�Yblock����0(�N�Nblock�����F��s��curFilledBlock)
            mBoard[curFilledBLock--][i] = block;
        while (curFilledBLock >= 0)//�U��������0
            mBoard[curFilledBLock--][i] = 0;
    }
}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int j = 0; j < mNZ; j++){
        block = 0, curFilledBLock = 0;
        for (int i = 0; i < mNX; i++) //�q����k
        {
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[j][curFilledBLock] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[j][curFilledBLock] = block * 2;
                curFilledBLock++;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[j][curFilledBLock] = block;
                block = mBoard[j][i];
                curFilledBLock++;
            }

        }
        if (block)
            mBoard[j][curFilledBLock++] = block;
        while (curFilledBLock < mNZ)
            mBoard[j][curFilledBLock++] = 0;
    }
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
	int block, curFilledBLock;
    for (int j = mNZ - 1; j >= 0; j--) {
        block = 0, curFilledBLock = mNZ - 1;
        for (int i = mNX - 1; i >= 0; i--)//�q�k�쥪
        {
            mPreviousBoard[j][i] = mBoard[j][i];
            if (!block)
                block = mBoard[j][i];
            else if (block == mBoard[j][i]) {
                if (block * 2 == 4096)
                {
                    mBoard[j][curFilledBLock] = 0;
                    curFilledBLock--;
                    block = 0;
                    continue;
                }
                mBoard[j][curFilledBLock] = block * 2;
                curFilledBLock--;
                block = 0;
            }
            else if (0 != mBoard[j][i]) {
                mBoard[j][curFilledBLock] = block;
                block = mBoard[j][i];
                curFilledBLock--;
            }

        }
        if (block)
            mBoard[j][curFilledBLock--] = block;
        while (curFilledBLock >= 0)
            mBoard[j][curFilledBLock--] = 0;
    }
}

void MY_2048::generateNumbers_All_2to4( )//�H������2 or 4
{
    //
    // Implement your own stuff
    //
	 for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 2;
            int num;
            if (index == 0) num = 2;
            else if (index == 1) num = 4;
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::generateNumbers_All_2to8( )//�H������2 4 8
{
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 3;
            int num;
            if (index == 0) num = 2;
            else if (index == 1) num = 4;
            else if (index == 2) num = 8;
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int index = rand() % 11;
            int num = 2 << index;//2*2��0�� 1��...10��
            mBoard[j][i] = num;
        }
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;

    case 'a':
    case 'A':
        //flg_AutoPlay
		flg_AutoPlay = true;
        play_Auto();
        flg_AutoPlay = false;
        break;
	 case ' '://+++++
        flg_AutoPlay = !flg_AutoPlay;
        break;
    }
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//






void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;

    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
	play_Auto();
}

/*void MY_2048::copy(const int src[][MAX_2048_NX], int tgt[][MAX_2048_NX])
{
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            tgt[j][i] = src[j][i];
        }
    }
}*/

double MY_2048::computescore()
{
    double score = 0.0;
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            int num = mBoard[j][i];
            score += num * pow(num, 1.5);
        }
    }
    return score;
}

void MY_2048::play_Auto()
{
    
    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    
    //copy(mBoard, initBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            initBoard[j][i] = mBoard[j][i];
        }
    }
    double score[4];
    int level = 7;
    for (int i = 0; i < numSpecialKeys; i++) {
        unsigned char action = specialKeys[i];
        score[i] = play_Smart_Recursive(level, action,initBoard);
    }
    int action_index = 0;
    double best_score = score[action_index];
    for (int i = 1; i < numSpecialKeys; i++) {
        if (score[i] > best_score) {
            best_score = score[i];
            action_index = i;
        }

    }
    //copy(initBoard, mBoard);       
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = initBoard[j][i];
        }
    }
    performAction(specialKeys[action_index]);
    
    
}

double MY_2048::play_Smart_Recursive(int numSteps, unsigned char action_key,int board[][MAX_2048_NX])
{
    double tScore = 0.0;


    if (numSteps <= 0) {
        tScore = computescore();
        return tScore;
    }
    //copy(board, mBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = board[j][i];
        }
    }
    performAction(action_key);

    int initBoard[MAX_2048_NZ][MAX_2048_NX];
    //copy(mBoard, initBoard);
	for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            initBoard[j][i] = mBoard[j][i];
        }
    }
    double rate = 0.85;
    double score[4] = { 0.0 };
    int action_index = 0;
    double best_score = score[action_index];

    for (int i = 0; i < numSpecialKeys; i++) {
        score [i]= score[i] * pow(rate, numSteps)
            + play_Smart_Recursive(numSteps - 1, specialKeys[i],initBoard);
        if (score[i] > best_score)
        {
            best_score = score[i];
            action_index = i;
        }
    }
    return best_score;
}
