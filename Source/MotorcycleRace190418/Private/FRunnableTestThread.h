//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//
//using namespace std;
//
//
//DEFINE_LOG_CATEGORY_STATIC(TestLog, Log, All);
//IMPLEMENT_SIMPLE_AUTOMATION_TEST(FFRunnableTest, "MyTest.PublicTest.RunnableTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
///**route
// * 
// */
//class FRunnableTestThread : public FRunnable
//{
//public:
//	FRunnableTestThread(int16 _Index) : Index(_Index) {}
//
//	virtual bool Init() override
//	{
//		UE_LOG(TestLog, Log, TEXT("Thread %d Init"), Index);
//		return true;
//	}
//
//	virtual uint32 Run() override
//	{
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:1"), Index);
//		Sleep(10.0f);
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:2"), Index);
//		Sleep(10.0f);
//		UE_LOG(TestLog, Log, TEXT("Thread %d Run:3"), Index);
//		Sleep(10.0f);
//		return 0;
//	}
//
//	virtual void Exit() override
//	{
//		UE_LOG(TestLog, Log, TEXT("Thread %d Exit"), Index);
//	}
//private:
//	int16 Index;
//};
//
//bool FFRunnableTest::RunTest(const FString& Parameters)
//{
//	FRunnableThread::Create(new FRunnableTestThread(0), TEXT("TestThread0"));
//	FRunnableThread::Create(new FRunnableTestThread(1), TEXT("TestThread1"));
//	FRunnableThread::Create(new FRunnableTestThread(2), TEXT("TestThread2"));
//	return true;
//}
