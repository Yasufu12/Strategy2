#include"System.h"
#include <Utility/Utility.h>
//Singleton
suken::CSystem System;

suken::CSystem::CSystem(){
	startTime = 0;
	count = 0;
	fps = 60.0;		//0���Z��h������
	frame = 0;
	escapeFlag = false;
	targetFps = 0.0f;
	screenShotGrHandleAdress = nullptr;
	loadingImgPath = "";
}
suken::CSystem::~CSystem(){
	
}
void suken::CSystem::Awake(){
	//�Q�[���̒���{�ݒ�A���ʉ���������Ȃ�
	SetWindowIconID( 101 ) ;//�A�C�R���̂��
	SetGraphMode( WINDOW_WIDTH ,  WINDOW_HEIGHT , 32 ) ;//SetWindowSize(WINDOW_WIDTH , WINDOW_HEIGHT );
	ChangeWindowMode(TRUE);
	SetAlwaysRunFlag(TRUE);//�펞�N������̂�TRUE
	SetOutApplicationLogValidFlag( FALSE );//���O�o�͗}������̂�FALSE
	DxLib_Init(); 
	SetDrawScreen( DX_SCREEN_BACK );
	SetTransColor( 255 , 0 , 255 );	//�}�[���^����
	if(loadingImgPath != ""){
		loadingImg = LoadGraph(loadingImgPath.c_str());
	}
	DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,loadingImg,true);
	//���t���b�V�����[�g�̎擾
	HDC hdc;
	hdc = GetDC( GetMainWindowHandle() );//�f�o�C�X�R���e�L�X�g�̎擾
	refreshRate = GetDeviceCaps( hdc , VREFRESH );//���t���b�V�����[�g�̎擾
	ReleaseDC( GetMainWindowHandle() , hdc );//�f�o�C�X�R���e�N�X�g�̉��

	display = CreateDC(TEXT("DISPLAY") , nullptr , nullptr , nullptr);

#ifdef USE_LUA
	Lua = luaL_newstate();
#endif
	ScreenFlip();

	N = refreshRate;//1�b�Ɉ��fps���Z�o

	now = GetNowCount();
	localStandardTime = now;

}
int  suken::CSystem::GetLocalStandardTime(){
	return localStandardTime;
}
void suken::CSystem::SetUseThread_Awake(bool flag){
	useThread_AwakeFlag = flag;
}
bool suken::CSystem::GetUseThread_Awake(){
	return useThread_AwakeFlag;
}
void suken::CSystem::SetLoadingGraph(const std::string path){
	loadingImgPath = path;
}
void suken::CSystem::SetLoadingMinimalTime(int time){
	loadingMinimalTime = time;
}
void suken::CSystem::Wait_Loading(){
	int restTime = loadingMinimalTime - (GetNowCount()-localStandardTime);
	if(restTime > 0){
		WaitTimer(restTime);
	}
}
void suken::CSystem::Update(){
	//�Վ�
	//N = (int)(GetFps()+0.5);
	//
	now = GetNowCount();
	if( count == 0 ){ //1�t���[���ڂȂ玞�����L��
		startTime = now;
	}
	if( count == N ){ //�K��t���[���ɒB�����畽�ς��v�Z����
		
		fps = 1000/((now-startTime)/(double)N);
		count = 0;
		startTime = now;

	}

	count++;
	frame++;
}
void suken::CSystem::Wait(){
		
#ifdef DEBUG_DRAW
	DrawFormatString(0, 5, WHITE, "%.1f", fps);
#endif
	if(targetFps != 0.0f){
		int tookTime = now - startTime;	//������������
		int waitTime = count*1000/targetFps - tookTime;	//�҂ׂ�����
		if( waitTime > 0 ){
		Sleep(waitTime);	//�ҋ@
		}
	}else{
		Sleep(0);	//�]�����^�C���X���C�X��j��
	}	
}
void suken::CSystem::End(){
	DxLib_End();	
	ShellExecute(GetMainWindowHandle() , "open" , "Launcher.exe" , nullptr , nullptr , SW_SHOW);
}
void suken::CSystem::TakeScreenShot(){
	if(screenShotFlag){
		screenShotFlag = false;
		if(screenShotGrHandleAdress != nullptr){
			*screenShotGrHandleAdress = GetDrawScreen();
		}
		screenShotGrHandleAdress = nullptr;
	}
}
void suken::CSystem::GetScreenShot(int *GrHandleAdress){
	screenShotFlag = true;
	screenShotGrHandleAdress = GrHandleAdress;
}
void suken::CSystem::Escape(){
	escapeFlag = true;
}
bool suken::CSystem::GetEscapeFlag(){	
	return escapeFlag;
}
int suken::CSystem::GetFrame(){
	return frame;
}
int suken::CSystem::GetNow(){
	return now;
}
float suken::CSystem::GetFps(){
	return fps;
}
int suken::CSystem::GetRefreshRate(){
	return refreshRate;
}
void suken::CSystem::SetTargetFps(float _fps){
	targetFps = _fps;
}
float suken::CSystem::GetTargetFps(){
	return targetFps;
}
//�V�����X���b�h�����B
void suken::CSystem::CreateNewThread( void(*pFunc)() ){
	if(handleChild.empty()){				
		DxLib::SetMultiThreadFlag( true );			//���̂܂܂ł�DxLib��DirectX�̊֌W�Ń}���`�X���b�h�ɂł��Ȃ��̂Őݒ肵�Ă��K�v������
	}
	//�V�����X���b�h���쐬�i�^�uHANDLE�v�̓|�C���^�Ȃ̂�System::CreateNewThread���\�b�h���I�����Ă������I�ɔj������Ȃ��j
	HANDLE handle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pFunc, nullptr, 0, LPDWORD());

	handleChild.push_back(handle);
}
HDC suken::CSystem::GetDisplayDC(){
	return display;
}
#ifdef USE_LUA
lua_State* CSystem::GetLua(){
	return Lua;
}
#endif