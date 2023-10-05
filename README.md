# Cpp_Design_Pattern

# 2023.10.04

# Mediator Pattern

<중재자 패턴>

모든 클래스간의 복잡한 로직(상호작용)을 캡슐화하여 하나의 클래스에 위임하여 처리하는 패턴 M:N의 관계에서 M:1의 관계로 복잡도를 떨어뜨려 유지 보수 및 재사용의 확장성에 유리하다. 하나의 클래스가 떠맡아 처리해야 하므로 God(신) 클래스가 될 수 있으므로 주의해야 한다. 비슷한 패턴으로 퍼샤드(Facade) 패턴과 옵저버(Observer) 패턴이 있다.

# 2023.10.05

<반복자 패턴>

Iterator pattern은 리스트/스택/트리 등 자료구조를 노출하지 않고 내부의 모든 항목에 접근할 수 있게 해주는 방법을 제공하는 패턴, 반복자 패턴이라고도 하며 쉽게 이야기하면 접근기능과 자료구조를 분리하여 객체화

->Collection의 예시로 들었을 때. Collection은 단순한 container에 불과함
->그러나 Collection과는 관계없이, 다른 코드가 해당 elements를 사용할 수 있도록 액세스하는 방법을 제공해야 한다.

->이 때 iterator 패턴을 사용하여 여러 search alg를 구현하여 사용
->각 search alg는 동일한 interface를 가지고 있으며 이렇게 하면 iterator라고 불리는 별도의 object로 collection의 순회 동작 추출 가능
->여러 iterator object들은 동시에 동일한 collection을 이동 가능

*구성

->iterator interface: Collection통과에 필요한 작업을 선언(현재 위치 검색/ 반복 다시 시작 등)
->Concrete iterator: 컬렉션을 통과하기 위한 특정 알고리즘 구현(여러 반복자가 동일한 컬렉션을 이동할 수 있게)
->Collection interface:컬렉션과 호환되는 iterator를 얻기 위한 하나 이상의 method 선언
->Concrete collection: Client가 요청할 때 마다 특정 concrete iterator class의 새 instance를 반환
->Client: interface를 통해 collection혹은 iterator와 함께 작동


*구현

->iterator interface를 선언한 다음 collection에서 next element를 가져오는 method가 필요함
->collection interface를 선언하고 fetching iterator를 가져오는 method선언
->iterator를 사용하여 통과할 수 있는 collection에 대해 구체적인 iterator class 선언
->collection class에 collection interface 구현
->client code를 검토하여 모든 traversal code를 iterator 사용으로 변경

*장단점

-장점
->단일 책임 원칙 준수
->개방/폐쇄 원칙 준수
->각 iterator object는 고유한 반복 상태를 포함하기 때문에 동일한 collection에 대해 parrellel로 반복 가능
->같은 이유로 iteration을 지연시키고 필요할 때 continue 가능

추상화: 반복자는 컬렉션의 내부 구조에 대한 상세 정보를 숨기고, 클라이언트에게 단순화된 인터페이스를 제공한다. 이로 인해 클라이언트 코드는 컬렉션의 구현 세부사항에 의존하지 않게 되므로, 변경에 대한 영향을 최소화할 수 있다.

다형성: 같은 반복자 인터페이스를 사용하여 다양한 종류의 컬렉션을 순회할 수 있다. 예를 들어, 배열이나 리스트, 트리 등 다른 데이터 구조도 동일한 방식으로 접근할 수 있다.

모듈성: 컬렉션과 그것을 순회하는 로직이 분리되므로, 각각 독립적으로 수정하거나 확장하기 쉽다.

여러 반복: 한 컬렉션에 대해 여러 개의 반복자를 동시에 사용할 수 있다. 이는 알고리즘에서 유용하게 사용될 수 있는데, 예를 들어 두 개의 포인터가 서로 다른 속도로 움직여야 하는 "두 포인터" 알고리즘에서 이런 기능이 필요하다.

일관된 방식으로 요소 접근: 모든 타입의 컬렉션이 공통된 인터페이스를 가지게 되므로 프로그램 전체에서 일관된 방식으로 요소들을 접근할 수 있게 된다.
제어 흐름의 단순화: 일반적인 for-loop나 while-loop보다 반복자가 제공하는 메서드(hasNext, next 등)를 사용함으로써 제어 흐름을 더욱 단순하게 만들 수 있다.

*추상화에 대한 분석

"내부 구조를 숨긴다"는 말은 데이터 구조의 내부 동작 방식이나 구현 세부사항을 외부에서 알 수 없도록 추상화하는 것을 의미한다. 이는 캡슐화(encapsulation)라는 객체 지향 프로그래밍의 핵심 원칙 중 하나를 반영한 것이다.

예를 들어, 배열, 연결 리스트, 트리 등은 모두 컬렉션(collection)으로서 여러 요소들을 저장하고 관리하는 역할을 하지만, 각각의 내부 구조와 동작 방식은 다르다. 배열은 인덱스를 통해 빠른 접근이 가능하지만, 연결 리스트는 순차적인 접근이 필요하며, 트리는 계층적인 구조로 데이터에 접근합니다.

반복자 패턴을 사용하면 이런 세부적인 차이점들을 클라이언트 코드로부터 숨길 수 있다. 즉, 반복자가 제공하는 next(), hasNext() 등의 메서드를 통해 컬렉션의 요소들에 일관되게 접근할 수 있게 된다. 이로 인해 클라이언트 코드는 컬렉션이 어떤 종류인지, 어떻게 동작하는지 알 필요 없이 해당 컬렉션에 있는 모든 요소들을 순회할 수 있다.

따라서 "내부 구조를 숨긴다"는 것은 클라이언트 코드가 데이터 구조의 내부 동작 방식과 세부사항에 의존하지 않도록 만드는 것으로서, 코드의 유연성과 재사용성을 높여준다.

-단점
->프로그램이 간단한 collection에서 작동할 때에는 과할 수 있다.
->iterator을 사용하는 것은 일부 specialized collection에서는 비효율적일 수 있다.
