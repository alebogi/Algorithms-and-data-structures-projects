program dz1p1;
const
  MAX=1000;
type
  matrica=array [1..MAX] of integer;
var
  opcija, dim, podr, nepodrUK, podrUK:integer;
  M:matrica;
Procedure KreirajMatricu(var m:matrica; var n:integer);     //PRVA STAVKA
var i,j,adr:integer;
begin
  writeln('Da bi matrica bila trougaona, mora biti kvadratna, zbog toga unesite jedan broj za dimenziju matrice.');
  write('Dimenzija: ');
  readln(n);
  for i:=1 to n do
  begin
     for j:=1 to n do
     begin
      if (i>j) then
      begin
        adr:=((i-1)*(i-2)) div 2 +j;
        write('Unesite element na poziciji [',i,',',j,']: ');
        readln(m[adr]);
      end;
     end;
  end;
end;
Procedure PodrazumevaniElement(var m:matrica; n:integer; var broj:integer);     //DRUGA STAVKA
begin
  writeln('Unesite podrazumevani element marice: ');
  readln(broj);
end;
Procedure DohvatiElement(var m:matrica; n:integer; podr:integer);           //TRECA STAVKA
var i,j,adr:integer;
begin
  writeln('Unesite poziciju elementa (i,j): ');
  readln(i, j);
  if (i>0) and (i<=n) and (j>0) and (j<=n) then
  begin
    if (i<=j) then
      writeln('Trazeni element je: ', podr)
    else
     begin
       adr:=((i-1)*(i-2)) div 2 +j; //adresa zeljenog elementa
       writeln('Trazeni element je: ', m[adr]);
     end;
  end
  else
    writeln('Trazena pozicija ne pripada opsegu ove matrice.');
end;
Procedure PostaviVrednost(var m:matrica; n,podr:integer);           //CETVRTA STAVKA
var i,j,adr,vrednost:integer;
begin
  writeln('Unesite poziciju elementa (i,j): ');
  readln(i, j);
  if (i>0) and (i<=n) and (j>0) and (j<=n) then
  begin
    if (i<=j) then
      writeln('Trazeni element je vec postavljen na vrednost ', podr,' i ne moze mu se menjati vrednost jer su gubi oblik trougaone matrice.')
    else
     begin
       adr:=((i-1)*(i-2)) div 2 +j; //adresa zeljenog elementa
       writeln('Unesite zeljenu vrednost: ');
       readln(vrednost);
       m[adr]:=vrednost;
     end;
  end
  else
    writeln('Trazena pozicija ne pripada opsegu ove matrice.');
end;
Procedure BrNepodrazumevanih(var m:matrica; var n,NEpodrazumevani,podrazumevani:integer);         //PETA STAVKA
begin


  NEpodrazumevani:=( n*(n-1)) div 2;    //br nenultih
  podrazumevani:= n*n - NEpodrazumevani;    //broj nultih elemenata
  writeln('Ukupan broj nepodrazumevanih elemenata iznosi: ', NEpodrazumevani);
end;
Procedure IspisMatrice(var m:matrica; n,podr:integer);                     //SESTA STAVKA
var i, j, adr:integer;
begin
  for i:=1 to n do
  begin
     for j:=1 to n do
     begin
        if (i<=j) then
         write(podr,' ')
         else
          begin
            adr:=((i-1)*(i-2)) div 2 +j;
            write(m[adr],' ');
          end;
     end;
     writeln();
  end;
end;
Procedure UstedaMemorije(m:matrica; n,podr:integer);               //SEDMA STAVKA
var usteda:real;
begin
  usteda:=((podr) / (n*n) )*100;  //broj podrazumevanih podeljen sa ukupnim brojem elemenata
  writeln('Ostvarena usteda memorijskog prostora iznosi: ', usteda:0:2, '%');
end;
Procedure Brisanje(var m:matrica; var n:integer);                                 //OSMA STAVKA
var i:integer;
begin
  Writeln('Program nije sposoban da fizicki obrise matricu, ali zato postavlja sve njene vredosti na 0 ');
  for i:=1 to n do
  m[i]:=0;
  n:=0;
end;
begin //glavni program
  writeln('Rad sa strogo donje trougaonom matricom');
  writeln();
  writeln('        Meni');
  writeln();
  writeln('**************************************************************************************');
  writeln('NAPOMENA-Da bi program uspeno radio, prvo izaberite opciju 1 i kreirajte svoju matricu');
  writeln('---------------------------------------------');
  writeln('1 - Kreiranje matrice');
  writeln('2 - Podrazumevani element');
  writeln('3 - Dohvatanje elementa matrice');
  writeln('4 - Postavljanje vrednosti elementu matrice');
  writeln('5 - Broj nepodrazumevanih elemenata');
  writeln('6 - Ispis matrice');
  writeln('7 - Usteda memorije');
  writeln('8 - Brisanje matrice');
  writeln('9 - Prekid programa');
  writeln('---------------------------------------------');
  writeln('Unesite redni broj zeljene opcije: ');
  readln(opcija);
  writeln('---------------------------------------------');

  while (opcija<>9) do
  begin
     case(opcija) of
		1: KreirajMatricu(M,dim);
		2: PodrazumevaniElement(M,dim,podr);
		3: DohvatiElement(M,dim,podr);
		4: PostaviVrednost(M,dim,podr);
		5: BrNepodrazumevanih(M,dim,nepodrUK,podrUK);
		6: IspisMatrice(M,dim,podr);
		7: UstedaMemorije(M,dim,podrUK);
                8: Brisanje(M,dim);
                9: Exit;
		end;


       writeln();
       writeln();
       writeln('=============================================');
       writeln('        Meni');
       writeln('---------------------------------------------');
       writeln('1 - Kreiranje matrice');
       writeln('2 - Podrazumevani element');
       writeln('3 - Dohvatanje elementa matrice');
       writeln('4 - Postavljanje vrednosti elementu matrice');
       writeln('5 - Broj nepodrazumevanih elemenata');
       writeln('6 - Ispis matrice');
       writeln('7 - Usteda memorije');
       writeln('8 - Brisanje matrice');
       writeln('9 - Prekid programa');
       writeln('---------------------------------------------');
       writeln('Unesite redni broj zeljene opcije: ');
       readln(opcija);
       writeln('---------------------------------------------');
  end;
end.

