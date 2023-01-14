# readingroom
독서실 관리 프로그램

1학기를 마치고 진행한 프로젝트로 가상의 독서실에서 좌석에 회원을 등록, 삭제하고 좌석 현황을 확인할 수 있는 기능을 구현하였습니다. 구조체와 파일 입출력 등 C언어의 내용들을 복습해 보며 하나의 프로젝트를 초기 완성 후 유지보수하였습니다.
구조체 배열로 좌석을 선언하고 등록된 좌석 정보를 파일에 입력하여 프로그램을 종료하여도 정보가 계속 저장되어 다시 실행시켰을 때 불러올 수 있도록 하였습니다. 또, 실행 시 마지막 수정 날짜와 현재 날짜 간의 차이를 계산하여 좌석 정보를 업데이트하도록 하였는데 이 과정에서 윤년인 경우를 고려하도록 하였습니다.

<주요 기능>

- 메뉴

실행 시 아래와 같은 메뉴 화면이 뜨고 아래에는 그 날의 날짜를 표시합니다. 화살표를 위아래로 움직이며 메뉴를 선택할 수 있습니다.

<img width="719" alt="image" src="https://user-images.githubusercontent.com/105623744/212464588-9861e643-7564-4730-a3d1-456ae8c13315.png">

- 등록

등록 메뉴 선택 시 '원하는 자리를 선택하세요' 라는 메세지와 함께 빈 자리의 번호들을 출력합니다. (전체 좌석은 30자리로 설정하였습니다.)

<img width="593" alt="image" src="https://user-images.githubusercontent.com/105623744/212464651-2c48f15f-f292-45b0-9980-ef6243a7927c.png">

좌석 번호를 입력하고 엔터를 누르면 사용자 정보를 입력받아 좌석을 등록된 것으로 처리합니다.

<img width="523" alt="image" src="https://user-images.githubusercontent.com/105623744/212464695-feb33379-ee29-436a-99d5-7b5da30635a8.png">

각 입력에서 올바른 값을 입력하지 않은 경우에 대해 예외처리를 수행하였습니다.

<img width="532" alt="image" src="https://user-images.githubusercontent.com/105623744/212464716-7410bcd7-5351-470e-80eb-3c6d4c1309aa.png">

- 삭제

삭제 메뉴 선택 시 '삭제하고 싶은 자리를 선택하세요'라는 메세지와 함께 등록된 자리 번호들을 출력하고, 올바른 값을 입력받으면 사용자 정보와 함께 정말로 삭제할지 한 번 더 물어보고 'y'를 입력 받으면 좌석 정보를 없애고 빈 자리로 처리합니다.

<img width="343" alt="image" src="https://user-images.githubusercontent.com/105623744/212464802-8af91791-8fb7-41f8-9e53-ecabb4e3ea72.png">

- 자리 현황

자리 현황 메뉴 선택 시 빈 자리와 사용 중인 자리의 색을 달리하여 아래와 같이 출력해 줍니다. 좌석 번호를 입력하여 좌석 정보를 확인할 수도 있습니다.

<img width="394" alt="image" src="https://user-images.githubusercontent.com/105623744/212464967-b5df30b9-bf77-4664-a7d2-f7265777c0da.png">

- 종료

종료 메뉴 선택 시 프로그램이 종료되고, 모든 좌석 정보는 txt파일에 저장됩니다.



<주요 소스 코드와 알고리즘>

- 좌석 구조체

아래와 같이 좌석의 빈 자리 여부, 사용자 이름, 이용 기간을 멤버로 갖고 있는 구조체 배열 s로 좌석 정보의 저장 구조를 생성하였습니다.

<img width="284" alt="image" src="https://user-images.githubusercontent.com/105623744/212465576-3150878f-d0af-48e6-b2df-a176eede358e.png">

- 현재 날짜 읽기

파일 실행시 현재 날짜를 읽어와 Y,M,D 변수에 각각 현재의 연,월,일을 저장합니다.

<img width="157" alt="image" src="https://user-images.githubusercontent.com/105623744/212465517-8e491331-4906-4430-aa2f-ff63cac26e7d.png">

- txt파일 읽어오기

현재 날짜를 읽어온 뒤 readfile(Y,M,D)함수를 실행하는데, 이 함수는 현재 날짜 정보를 매개변수로 받아 txt파일로부터 마지막 수정 날짜와 좌석 정보를 읽어 와 날짜 간의 차이를 계산하여 각 좌석의 남은 일수를 수정하거나, 남은 일수가 없는 경우 빈 자리로 새롭게 업데이트해 줍니다.

날짜 계산은 기본적으로 현재 일(D)에서 마지막 수정 일(d)을 빼서 계산하는데, 달이 바뀌거나 년도가 바뀌는 경우는 MtoD()라는 새로운 함수를 이용해 계산하도록 하였습니다. 날짜 계산 시 윤년인 경우도 고려하였습니다.

<img width="451" alt="image" src="https://user-images.githubusercontent.com/105623744/212465623-112876e7-edd6-4515-92c0-9459ffe281d6.png">

<img width="398" alt="image" src="https://user-images.githubusercontent.com/105623744/212465851-f72be569-2f39-4ad0-8dbb-02c2932ec616.png">

txt파일은 아래와 같이 맨 윗줄은 마지막 수정 날짜가 쓰여 있고, 아래에 좌석 정보가 한 줄씩 표시되어 있습니다.

<img width="85" alt="image" src="https://user-images.githubusercontent.com/105623744/212465910-824ffae8-e219-49ea-bb7e-0337afab7eb7.png">

- 등록, 삭제

등록은 enroll()함수로, 삭제는 erase()함수로 실행하는데 두 함수의 코드가 비슷하므로 등록 함수만 소개하겠습니다.

먼저 빈 자리의 개수를 카운트하여 빈 자리가 0인 경우 '빈 자리가 없습니다.'라는 메세지를 띄우고 3초 뒤에 메뉴로 돌아갑니다.

빈 자리의 개수가 0이 아니면 반복문으로 s[].using (각 좌석의 빈 자리 여부)가 1인 좌석의 번호들만 출력해 줍니다.
그 뒤 등록하고 싶은 자리 정보를 입력 받는데, while(1) 내에서 메뉴로 돌아가기(q)와 올바른 입력 값 범위, 그 외 다른 값을 입력 받는 경우로 나누어 각 경우에 올바르지 않은 입력일 경우 다시 입력하도록 합니다.

<img width="536" alt="image" src="https://user-images.githubusercontent.com/105623744/212466128-1a824db8-f905-4197-ab45-a5cc4329b934.png">



<프로그램 수정 내용>

프로그램을 7월에 초기 완성 후 부족한 것들을 조금씩 수정하였습니다.

- 날짜 계산 기능 : 처음에 파일에 좌석 정보만 입력하고 날짜에 상관없이 좌석 정보만 그대로 불러왔는데, 마지막 수정 날짜로부터 현재 날짜까지의 일을 계산하여 그에 맞게 좌석 정보를 업데이트해 표시하도록 수정하였습니다.

- 윤년 고려와 년도 계산 : 처음에는 윤년과 년도가 바뀌는 경우를 고려하지 않았던 점을 개선하였습니다.

- 등록, 삭제에서 번호를 입력한 뒤 엔터를 두 번 쳐야 하는 문제 : 처음 소스코드를 작성했을 때 이런 문제가 발생했는데, 문자 입력에 대해 예외처리를 하기 위해 getchar()로 다시 입력을 받도록 하여 이런 문제가 발생했고, 코드를 수정하여 개선하였습니다.

- 문자입력 예외처리 : 숫자를 입력해야 할 때 문자를 입력하여 발생하는 오류를 수정하였습니다.

