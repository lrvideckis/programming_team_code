" coloring
colorscheme default
syntax on
set t_Co=256

" locative
set number
set cursorline
set relativenumber

" menu
set wildmenu

" searching
set hlsearch
set ignorecase
set smartcase
set incsearch

" spacing
filetype indent on
set ai
set si
set cindent
set tabstop=4
set shiftwidth=4
set softtabstop=4
set pastetoggle=<f1>
set listchars=tab:\|\ ,trail:_ list
cal matchadd('ColorColumn', '\%81v.', 100)

function! StripTrailingWhitespace()
	normal mZ
	let l:chars = col("$")
	%s/\s\+$//e
	normal `Z
endfunction

autocmd BufWritePre * call StripTrailingWhitespace()

" speed
inoremap kj <ESC>

" syntactical
set showmatch
set matchpairs+=<:>
let c_no_curly_error=1
inoremap {<CR> {<CR>}<ESC>O

" template (add for each file type and extension)
autocmd BufNewFile *.cpp -r ~/programming_team_code/library/contest/template.cpp

" test
autocmd filetype cpp noremap <F5> :w!<CR>:<C-u>!g++ -std=c++17 -Wall %:r.cpp && cat > in &&
			\ ./a.out < in && rm a.out in<CR>

autocmd filetype cpp noremap <F6> :w!<CR>:<C-u>!g++ -Wall -Wextra -pedantic -Wno-unused-result
			\ -DLOCAL -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal
			\ -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG
			\ -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=undefined
			\ -fno-sanitize-recover=all -fstack-protector %:r.cpp &&
			\ cat > in && ./a.out < in && rm a.out in<CR>

autocmd filetype cpp noremap <F7> :w!<CR>:<C-u>!g++ -g -Wall -Wextra -pedantic -Wno-unused-result
			\ -DLOCAL -std=c++17 -Wshadow -Wformat=2 -Wfloat-equal -Wcast-qual
			\ -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC
			\ -fsanitize=undefined -fno-sanitize-recover=all
			\ -fstack-protector %:r.cpp && cat > in &&
			\ gdb -q -ex 'set args < in' a.out && rm a.out in<CR>

map <F8> :setlocal spell! spelllang=en_us<CR> " check spelling with F8

" <F1> to toggle pasting w/o indentation in insert mode
" <F5> fast compile
" <F6> debug compile
" <F7> debug compile and debug with GDB
" <F8> check spelling
