//
// 全てのステートの親クラス
//

#pragma once


template <class entity_type>
class State{

public:
	virtual ~State(){}

	virtual void Enter(entity_type*) = 0;		// このステートに入ったときの処理

	virtual void Execute(entity_type*) = 0;		// このステート中の処理

	virtual void Exit(entity_type*) = 0;		// このステートから出るときの処理

};