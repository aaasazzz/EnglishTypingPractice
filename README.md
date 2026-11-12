# 영어 타자 연습 (English Typing Practice)

1학년(2022) 때 C++과 DxLib로 만든 영어 타자 연습 프로그램을 리팩토링하는 저장소입니다.
원본 코드는 첫 커밋(`a428417`)에 그대로 남아 있고, 이후 커밋과 PR이 수정 과정입니다.

- 메뉴: Spot Practice(글자), Word Practice(단어), Short Writing Practice(문장), Long Writing Practice(긴 글)
- 조작: 위/아래 키로 메뉴 이동, Enter 선택, F11 전체화면, ESC 창모드 / 종료
- 실행: Windows + Visual Studio + [DxLib](https://dxlib.xsrv.jp/), `resources` 폴더를 실행 폴더에 둔다.

## 수정 내역

### PR #1 `chore/utf8-encoding`

| 문제 | 수정 |
|---|---|
| `code.cpp`가 CP949로 저장되어 mac에서 한글 주석이 깨짐 | UTF-8(BOM)으로 변환 (코드 변경 없음) |

### PR #2 `refactor/resources-folder`

| 문제 | 수정 |
|---|---|
| txt, png 파일이 프로젝트 루트에 흩어져 있음 | `resources/`, `resources/long_writing/` 폴더로 정리 |
| 파일 경로가 코드 여러 곳에 하드코딩됨 | 경로를 `ResourcePaths` 구조체 하나로 모음 |
| 긴 글 연습 텍스트가 저작권 있는 노래 가사 | public domain 글 3편으로 교체 (*Alice's Adventures in Wonderland*, *Peter Pan*, *The Wonderful Wizard of Oz*, 출처: Project Gutenberg) |
| 긴 글 메뉴가 고정 크기 배열 + 항목마다 `if/else` 분기라 글을 바꾸려면 여러 곳을 고쳐야 함 | `vector` + 반복문으로 변경, 항목 개수는 글 목록 크기로 계산 |
| 긴 글 메뉴에 다시 들어가면 강조 표시와 실제 선택이 어긋남 | 메뉴에 들어올 때 강조 위치를 0번 항목이 아닌 현재 선택 번호 기준으로 설정 |
| `short.txt`의 둥근 따옴표(`’`)는 키보드로 칠 수 없어 항상 오타 처리됨 | `'`로 변경 |

### PR #3 `fix/bugs-and-unsafe-code`

| 문제 | 수정 |
|---|---|
| 한 줄을 Enter로 끝내면 다음 입력이 빈 값으로 바로 제출됨 (긴 글이 한 줄씩 밀림) | `KeyInputString` 전에 Enter를 뗄 때까지 기다린 뒤 입력 버퍼 비우기 (`ClearPendingInput()`) |
| 메인 루프에서 배경 이미지를 매 프레임 `LoadGraph`로 새로 불러옴 | 루프 밖에서 한 번만 불러오기 |
| 위 수정 후 전체화면 / 창모드 전환 시 배경이 사라짐 (화면 모드 전환 시 이미지 핸들 리셋) | 화면 모드를 바꾼 직후 배경 다시 불러오기 |
| a를 `char` 배열에 복사할 때 `'\0'`을 한 칸 뒤에 넣어 경로 뒤에 쓰레기 값이 붙을 수 있음 | string -> char* 변환 로직을 복사 후 `'\0'` 추가에서 c_str()로 수정|
| 입력 배열의 크기와 함수로 받는 크기가 불일치하여 overflow문제 발생 가능 | 읽기, 입력 최대 길이를 버퍼 크기에 맞춤 |
