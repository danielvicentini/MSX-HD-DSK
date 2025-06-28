# MSX-HD-DSK para PC

(c) junho 2025 - Daniel Vicentini (danielvicentini@hotmail.com)

# Sobre

- Programa em modo de linha de comando que permite criar imagem de HD para MSX-DOS no padrão FAT 16 e usar nos emuladores de MSX.
- O programa permite escolher entre um tamanho mínimo de 32MB e máximo de 4GB (limite do padrão FAT16).



# Como usar

- Rodar o arquivo .exe (neste GIT já pré-compilado Windows com gcc 14.2 versão padrão de 64 bits ou 32 bits).
- Não é necessário usar nenhum parâmetro.
- O arquivo *msxdos_image.dsk* será criado no diretório atual.



# Uso nos emuladores


- Necessário criar devidas partições de acordo com o interface de drive em uso.
- Testado com o Nextor 2.x. Ao inserir o disco, inicilizar no MSX-Basic. Executar o comando 'call fdisk' para preparação do disco.




