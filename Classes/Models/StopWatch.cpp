//
//  StopWatch.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/27.
//
//

#include "Models/StopWatch.h"

// 初期化
bool StopWatch::init(const double& init_time)
{
    // 初期時間のセット
    this->time = init_time;
    return true;
}

bool StopWatch::init(const int init_time)
{
    return this->init(static_cast<double>(init_time));
}

// 時間計測開始
void StopWatch::tic()
{
    this->start_time = this->getSecMs();
}

// 時間計測停止
void StopWatch::toc()
{
    double start = this->start_time;
    double stop = this->getSecMs();
    double interval_time = stop - start;
    this->time += interval_time;
}

// 時間取得
double StopWatch::getSecMs(){
    timeval tv;
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec) + (tv.tv_usec) * 1e-6;
}

// 経過時間を取得
double StopWatch::getTime()
{
    this->toc();
    this->tic();
    return this->time;
}

// 経過時間を秒で取得
int StopWatch::getTimeInt()
{
    return floor(this->getTime());
}