#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()

public:	
	AABFountain();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	/*
		Visible : 읽기전용 , Edit : 수정가능
		AnyWhere :  , DefaultOnly : 런타임에서만 읽기 전용으로 사용 , InstanceOnly : 인스턴스에만 ㅅ ㅗㄱ하도록 지정하고 클래스 수준에서는 공유하지 않는다.
		
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Water;
};
