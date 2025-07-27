07/27 기준 변경 사항 



-Engine/Game 영역 분리 



-GameObject Component 구조 변경

(고정적으로 필요한 컴포넌트 동적 추가-> 효율 떨어진다고 생각해서 멤버로 관리함.)

m\_transform, m\_spriterenderer



->m\_spriterenderer를 통해 assetmapping \& render를 진행함. 





p.s 이건 진짜 읽어줬음 함. 



Engine/Game 영역 분리로 인해 오브젝트\&Scene 생성 방식이 변경됨.



main 함수의 초기 부분 참고하면 기존 loop전에 실행되는 함수가 존재함. 



ObjectRegister(); 

SceneFactory::Get().SceneRegister();



ObjectFactory에 Object 생성자를 저장

SceneFactory에 Scene 생성자를 저장 



-> 후에 engine에서 factory를 통해 오브젝트와 Scene을 생성함



그렇기 때문에 오브젝트와 Scene을 생성하고 구체화 할 때 Factory에 등록하는 과정이 필수임 



