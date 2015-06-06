//
//  LoadScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "LoadScene.h"

const vector<Scene*> LoadScene::scenes =
{
	TitleScene::createScene()
};

// コンストラクタ
LoadScene::LoadScene()
{FUNCLOG}

// デストラクタ
LoadScene::~LoadScene()
{FUNCLOG}

// createScene関数
Scene* LoadScene::createScene(const SceneType& sceneType)
{
	Scene* scene = Scene::create();
	Layer* layer = LoadScene::create(sceneType);
	scene->addChild(layer);
	return scene;
}

// 初期化
bool LoadScene::init(const SceneType& sceneType)
{
	if(!Layer::init()) return false;
	
	// 別スレッドを生成して引数を渡して実行する
	thread th = thread([this] (int n) {
		mtx.lock();
		cout << "thread is: " << this_thread::get_id() << endl;
		mtx.unlock();
		
		for (int i = 0; i < 100000; i++) {
			mtx.lock();
			log("%d", n + i);
			mtx.unlock();
		}
		
		// 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
		Scheduler* scheduler = Director::getInstance()->getScheduler();
		scheduler->performFunctionInCocosThread(CC_CALLBACK_0(LoadScene::loadFinished, this));
	}, 100);
	
	// スレッドの管理を手放す
	// スレッドの処理を待つ場合はt.join()かstd::asyncを使う
	th.detach();
	
	// メインスレッドのThread Idを出力
	// 共有リソースを使うのでlock (これがなければ別スレッドに出力を割り込まれる)
	mtx.lock();
	cout << "thread is: " << this_thread::get_id() << endl;
	mtx.unlock();

	return true;
}

void LoadScene::loadFinished()
{
	FUNCLOG
	return;
}
