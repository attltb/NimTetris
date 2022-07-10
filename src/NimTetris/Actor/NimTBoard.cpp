#include "NimTBoard.hpp"
#include "DialogBox.hpp" //
#include "resource.h" //
#include <WinUser.h> //
#include <wtypes.h> //
using namespace std;
extern HINSTANCE g_hInst; //
extern HWND hWndMain; //
void NimTBoard::takePlayerInfoCallback(void* param) {
    NimTBoard* pBoard = (NimTBoard*)param;
    NimTetrisAutosaveds& autosaveds = pBoard->autosaveds;

    pair<NimTetrisAutosaveds*, int> param1 = make_pair(&autosaveds, 1);
    pair<NimTetrisAutosaveds*, int> param2 = make_pair(&autosaveds, 2);
    NimTetrisPlayerInfo playerInfo1_rev = autosaveds.lastPlayer1Info;
    NimTetrisPlayerInfo playerInfo2_rev = autosaveds.lastPlayer2Info;
    if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWndMain, SelectPlayerProc, (LPARAM)&param1) != IDOK) {
        autosaveds.lastPlayer1Info = playerInfo1_rev;
    }
    if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWndMain, SelectPlayerProc, (LPARAM)&param2) != IDOK) {
        autosaveds.lastPlayer2Info = playerInfo2_rev;
    }

    pBoard->player1 = NimTPlayer::create(autosaveds.lastPlayer1Info, pBoard->threadManager);
    pBoard->player2 = NimTPlayer::create(autosaveds.lastPlayer2Info, pBoard->threadManager);
    pBoard->turn = 1;
    pBoard->status = Status::PREPARED;
}

void NimTBoard::addDisabledMarks(const vector<pair<int, int>>& coodinates) {
    for (auto it = coodinates.begin(); it != coodinates.end(); it++) {
        disabledMarks.push_back(make_pair(make_pair(it->first, it->second), NimTDisabledMark(graphics)));
    }
}
void NimTBoard::addBlock(Tetromino10x10 block) {
    blocks.push_back(make_pair(make_pair(block.pos_y, block.pos_x), NimTBlock(graphics, block.tetrominoFixedID())));
}

void NimTBoard::input(Tetromino10x10 block) {
    if (!board.isPutable(block)) return;
    bool isPlayPrepared = getPlayingPlayer()->onUserInput(cursur);
    if (isPlayPrepared) applyPlay();
}

void NimTBoard::startGameOverAnim() {
    status = Status::GAMEOVERANIM;
    overAnim.start();
}
void NimTBoard::skipGameOverAnim() {
    overAnim.skip();
    status = Status::GAMEOVER;
}
void NimTBoard::proceed() {
    if (status == Status::GAMEOVERANIM) skipGameOverAnim();
    else if (status == Status::GAMEOVER) {
        if (resultSign == ResultSign::P1RESIGN) resultSign = ResultSign::P2WIN;
        else if (resultSign == ResultSign::P2RESIGN) resultSign = ResultSign::P1WIN;
        else askPlayerInfoAndReset();
    }
}
void NimTBoard::endGame(ResultSign _resultSign) {
    NimTPlayer* winner = getWaitingPlayer();
    NimTPlayer* loser = getPlayingPlayer();
    winner->onWin();
    loser->onLose();
    winner->getPlayerInfo().updateELO(loser->getPlayerInfo());

    resultSign = _resultSign;
    if (resultSign == ResultSign::P1WIN || resultSign == ResultSign::P2WIN) startGameOverAnim();
    else status = Status::GAMEOVER;
}
void NimTBoard::applyPlay() {
    Tetromino10x10 block = getPlayingPlayer()->endTurn();
    addBlock(block);
    addDisabledMarks(board.putAndMarkDisabled(block));
    if (board.isFull()) return endGame((turn == 1) ? ResultSign::P2WIN : ResultSign::P1WIN);
    else {
        changePlayingPlayer();
        getPlayingPlayer()->startTurn(block);
        animFrameNo = -1;
    }
}
void NimTBoard::applyResign() {
    return endGame((turn == 1) ? ResultSign::P1RESIGN : ResultSign::P2RESIGN);
}
void NimTBoard::askPlayerInfoAndReset() {
    status = Status::SETTING;

    if (player1) delete player1;
    if (player2) delete player2;

    takePlayerInfoThread = threadManager.newThread(takePlayerInfoCallback, this);
}
void NimTBoard::resetBoard() {
    blocks.clear();
    disabledMarks.clear();
    board.clear();
    overAnim.reset();
    cursur = Tetromino10x10();
}
void NimTBoard::startGame() {
    player1->initBoard(board);
    player2->initBoard(board);

    animFrameNo = -1;
    status = Status::PLAYING;
    turn = 1;
    player1->startTurn();
}
void NimTBoard::changePlayingPlayer() {
    if (turn == 1) turn = 2;
    else turn = 1;
}

void NimTBoard::onInitialize() {
    board.clear();
    askPlayerInfoAndReset();
}
void NimTBoard::onFrame(int frameNo) {
    animFrameNo++;
    frame.onFrame(frameNo);
    if (status == Status::PREPARED) {
        takePlayerInfoThread->free();
        resetBoard();
        startGame();
    }
    if (status == Status::PLAYING) {
        bool isPlayPrepared = getPlayingPlayer()->onFrame(frameNo);
        getWaitingPlayer()->onFrame(frameNo);
        if (isPlayPrepared) applyPlay();
    }
    else if (status == Status::GAMEOVERANIM) {
        if (overAnim.onFrame(frameNo)) status = Status::GAMEOVER;
    }
}
void NimTBoard::onKeyDown(KeyCode keycode) {
    if (status == Status::PLAYING) {
        switch (keycode) {
        case KeyCode::Left:
            cursur.move_l();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::Right:
            cursur.move_r();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::Up:
            cursur.move_u();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::Down:
            cursur.move_d();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::A:
            cursur.change_shape_left();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::S:
            cursur.rotate_right();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::D:
            cursur.change_shape_right();
            getPlayingPlayer()->onUserCursurMove(cursur);
            return;
        case KeyCode::Space:
        case KeyCode::Enter:
            return input(cursur);
        case KeyCode::R:
            if (getPlayingPlayer()->onUserResign()) applyResign();
            return;
        }
    }
    else proceed();
}
void NimTBoard::onMouseMove(int xPos, int yPos) {
    if (status != Status::PLAYING) return;
    if (!getPlayingPlayer()->showCursur()) return;

    int xPos_fixed = xPos - BOARD_FRAME_WIDTH;
    int yPos_fixed = yPos - BOARD_FRAME_HEIGHT;
    if (xPos_fixed < 0 || xPos_fixed > BOARD_BODY_WIDTH) return;
    if (yPos_fixed < 0 || yPos_fixed > BOARD_BODY_HEIGHT) return;

    double centerOfMass_x = cursur.tetrominoFixedInfo().centerOfMass_x;
    double centerOfMass_y = cursur.tetrominoFixedInfo().centerOfMass_y;
    double xBase_d = round(xPos_fixed/((double)BLOCK_INTERVAL_X) - centerOfMass_x);
    double yBase_d = round(yPos_fixed/((double)BLOCK_INTERVAL_Y) - centerOfMass_y);

    int xBase = (int)(xBase_d < 0 ? (xBase_d - 0.5) : (xBase_d + 0.5));
    int yBase = (int)(yBase_d < 0 ? (yBase_d - 0.5) : (yBase_d + 0.5));
    cursur.setPos(xBase, yBase);
    getPlayingPlayer()->onUserCursurMove(cursur);
}
void NimTBoard::onMouseLDown(int xPos, int yPos) {
    if (status == Status::PLAYING) input(cursur);
    else proceed();
}

Drawable NimTBoard::getScreen_Backlight() const {
    Drawable filter = Drawable::Filter(BOARD_BODY_WIDTH + 10, BOARD_BODY_HEIGHT + 10, Color32{ (uint8_t)255, (uint8_t)255, (uint8_t)255, (uint8_t)64 }, BlendMode::COVER);
    return Drawable::Moved(-5, -5, filter);
}
Drawable NimTBoard::getScreen_Places() const {
    vector<Drawable> drawables;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            PlaceState placeState = board.at[i][j];
            if (placeState == PlaceState::EMPTY) {
                drawables.push_back(Drawable::Moved(j * BLOCK_INTERVAL_X, i * BLOCK_INTERVAL_Y, graphics.place));
            }
        }
    }
    return Drawable::Composite(drawables);
}
Drawable NimTBoard::getScreen_DisabledMarks() const {
    vector<Drawable> drawables;
    for (auto it = disabledMarks.begin(); it != disabledMarks.end(); it++) {
        int y = it->first.first;
        int x = it->first.second;
        drawables.push_back(Drawable::Moved(x * BLOCK_INTERVAL_X, y * BLOCK_INTERVAL_Y, it->second.getScreen()));
    }
    return Drawable::Composite(drawables);
}
Drawable NimTBoard::getScreen_Blocks() const {
    vector<Drawable> drawables;
    for (auto it = blocks.begin(); it != blocks.end(); it++) {
        int y = it->first.first;
        int x = it->first.second;
        drawables.push_back(Drawable::Moved(x * BLOCK_INTERVAL_X, y * BLOCK_INTERVAL_Y, it->second.getScreen()));
    }
    return Drawable::Composite(drawables);
}
Drawable NimTBoard::getScreen_LightAnim() const {
    double lightMax = 0.2;
    double multiplier[20] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1};

    uint8_t light255 = (uint8_t)((lightMax * multiplier[animFrameNo % 20]) * 255.0);
    Drawable single = Drawable::Filter(BLOCK_INTERVAL_X, BLOCK_INTERVAL_Y, Color32{ (uint8_t)255, (uint8_t)255, (uint8_t)255, light255 }, BlendMode::COVER);
    vector<Drawable> drawables;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            PlaceState placeState = board.at[i][j];
            if (placeState == PlaceState::EMPTY) {
                drawables.push_back(Drawable::Moved(j * BLOCK_INTERVAL_X, i * BLOCK_INTERVAL_Y, single));
            }
        }
    }
    return Drawable::Composite(drawables);
}
Drawable NimTBoard::getScreen_Cursur() const {
    Drawable cursurGraphic = graphics.tetromino_cursurs[(int)cursur.tetrominoFixedID()];
    return Drawable::Moved(cursur.pos_x * BLOCK_INTERVAL_X, cursur.pos_y * BLOCK_INTERVAL_Y, cursurGraphic);
}
Drawable NimTBoard::getScreen_insideFrame() const {
    vector<Drawable> drawables;
    drawables.push_back(getScreen_Backlight());
    drawables.push_back(getScreen_Places());
    drawables.push_back(getScreen_DisabledMarks());
    drawables.push_back(getScreen_Blocks());
    if (status == Status::PLAYING) {
        //drawables.push_back(getScreen_LightAnim());
        if (getPlayingPlayer()->showCursur()) drawables.push_back(getScreen_Cursur());
    }
    drawables.push_back(overAnim.getScreen());
    return Drawable::Composite(drawables);
}

Drawable NimTBoard::getScreen() const {
    vector<Drawable> drawables;
    drawables.push_back(frame.getScreen());
    drawables.push_back(Drawable::Moved(BOARD_FRAME_WIDTH, BOARD_FRAME_HEIGHT, getScreen_insideFrame()));
    if (status == Status::GAMEOVER) {
        switch (resultSign) {
        case ResultSign::P1RESIGN:
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 280) / 2, (BOARD_HEIGHT - 40) / 2, graphics.oldResult[0]));
            break;
        case ResultSign::P2RESIGN:
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 280) / 2, (BOARD_HEIGHT - 40) / 2, graphics.oldResult[2]));
            break;
        case ResultSign::P1WIN:
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 472) / 2, ((BOARD_HEIGHT - 108) / 2) - 40, graphics.oldGameover));
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 280) / 2, ((BOARD_HEIGHT - 40) / 2) + 40, graphics.oldResult[1]));
            break;
        case ResultSign::P2WIN:
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 472) / 2, ((BOARD_HEIGHT - 108) / 2) - 40 , graphics.oldGameover));
            drawables.push_back(Drawable::Moved((BOARD_WIDTH - 280) / 2, ((BOARD_HEIGHT - 40) / 2) + 40, graphics.oldResult[3]));
            break;
        }
    }
    return Drawable::Composite(drawables);
}