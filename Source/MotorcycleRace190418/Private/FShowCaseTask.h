//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//
//using namespace std;
//
//DEFINE_LOG_CATEGORY_STATIC(TestLog, Log, All);
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFRunnableTest, "MyTest.PublicTest.Runnable", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
///**
// * 
// */
//class FShowCaseTask
//{
//public:
//	FShowCaseTask();
//	~FShowCaseTask();
//
//	FShowCaseTask(int16 _Index) : Index(_Index) {}
//
//	static const TCHAR* GetTaskName()
//	{
//		return TEXT("FShowcaseTask");
//	}
//
//	FORCEINLINE static TStatId GetStatId()
//	{
//		RETURN_QUICK_DECLARE_CYCLE_STAT(FShowCaseTask, STATGROP_TaskGraphTasks);
//	}
//
//	static ENamedThreads::Type GetDesiredThread()
//	{
//		return ENamedThreads::AnyThread;
//	}
//
//	static ESubsequentsMode::Type GetSubsequentsMode()
//	{
//		return ESubsequentsMode::TrackSubsequents;
//	}
//
//	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
//	{
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:1"), Index);
//		Sleep(10.0f);
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:2"), Index);
//		Sleep(10.0f);
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:3"), Index);
//		Sleep(10.0f);
//	}
//
//private:
//	int16 Index;
//};
//
//
//
//bool FMyTaskGraphTest::RunTest(const FString& Parameters)
//{
//	TGraphTask<FShowCaseTask>::CreateTask(NULL, ENamedThreads::GameThread).ConstructAndDispatchWhenReady(0);
//	TGraphTask<FShowCaseTask>::CreateTask(NULL, EnamedThreads::GameThread).ConstructAndDispatchWhenReady(1);
//	TGraphTask<FShowCaseTask>::CreateTask(NULL, EnamedThreads::GameThread).ConstructAndDispatchWhenReady(2);
//	return true;
//}
//
