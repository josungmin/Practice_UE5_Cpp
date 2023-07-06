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
		Visible : �б����� , Edit : ��������
		AnyWhere :  , DefaultOnly : ��Ÿ�ӿ����� �б� �������� ��� , InstanceOnly : �ν��Ͻ����� �� �Ǥ��ϵ��� �����ϰ� Ŭ���� ���ؿ����� �������� �ʴ´�.
		
	*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Mesh")
	TObjectPtr<class UStaticMeshComponent> Water;
};
