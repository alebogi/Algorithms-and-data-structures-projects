program dz1p2;
type
  niz=array [1..1000] of integer;
var
  duzinaSTEK,k,broj,opcija,q:integer;
  stek,dno,vrh:niz;

Procedure StvaranjeSteka(var br,k,n:integer; var vrh,dno:niz);   //PRVA STAVKA
var i:integer;
begin
  write('Unesite sa koliko stekova zelite da radite: ');
  readln(br);
  write('Unesite pocetni kapacitet stekova: ');
  readln(k);
  n:=br*k;
  if (n>1000) then
    writeln('Nema dovoljno memorije da bi se ostvarila zeljena opcija.')
  else
    begin
      vrh[1]:=0;
      dno[1]:=0;
      for i:=2 to br do    //duzina niza sa vrhovima i dnom je zapravo broj stekova
       begin
          vrh[i]:=k+vrh[i-1];
          dno[i]:=k+dno[i-1];
       end;
      writeln('Uspesno ste kreirali stekove.');
    end;
end;
Procedure DodajOdredjeno(var br,k,n,q:integer; var vrh,dno,stek:niz);  //DRUGA STAVKA
var i,unos,vrednost,prosirenje:integer;
begin
  write('Unesite redni broj steka na koji zelite da dodate vrednost: ');
  readln(unos);
  if (unos>br) then
    writeln('Broj premasuje broj stekova.')
  else
    begin       //provera popunjenosti
      if (vrh[unos]=dno[unos+1]) and (q<>1) then  //popunjen
        begin     //sledi provera popunjenosti okolnih stekova
          if (unos<>1) and (unos<>br) then   //nije prvi ili poslednji stek
          begin
           if ( (vrh[unos-1]-dno[unos-1])>(vrh[unos+1]-dno[unos+1]) ) then //provera da li je popunjeniji levi ili desni stek od unosa
             begin   //smestanje u desni +1
               if ( (vrh[unos+1]-dno[unos+1]) < (k*60/100) ) then //ako je popunjenost manja od 60%
                 begin  //prosiruje na racun desnog steka      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    prosirenje:=(k*20) div 100;
                    for i:=vrh[unos+1] downto dno[unos+1] do
                        stek[i+prosirenje]:=stek[i];
                    dno[unos+1]:=dno[unos+1]+prosirenje;
                    vrh[unos+1]:=vrh[unos+1]+prosirenje;
                    write('Unesite vrednost koju hocete da dodate: ');
                    readln(vrednost);
                    stek[vrh[unos]+1]:=vrednost;
                    vrh[unos]:=vrh[unos]+1;
                    q:=1;
                 end
                else //popunjenost veca od 60% i ne moze se nista smestiti
                 writeln('GRESKA - Stek je popunjen, i ne moze se prosiriti.');
             end
           else
            begin  //smestanje u levi -1
               if ( (vrh[unos-1]-dno[unos-1]) < (k*60/ 100) ) then //ako je popunjenost manja od 60%
                begin  //prosiruje na racun levog
                    prosirenje:=(k*20) div 100;
                    for i:=dno[unos] to vrh[unos] do
                        stek[i-prosirenje]:=stek[i];
                    dno[unos]:=dno[unos]-prosirenje;
                    vrh[unos]:=vrh[unos]-prosirenje;
                    write('Unesite vrednost koju hocete da dodate: ');
                    readln(vrednost);
                    stek[vrh[unos]+1]:=vrednost;
                    vrh[unos]:=vrh[unos]+1;
                    q:=1;
                end
                else //popunjenost veca od 60% i ne moze se nista smestiti
                 writeln('GRESKA - Stek je popunjen, i ne moze se prosiriti.');
            end;
          end    //**************************************************GRANICNI SLUCAJEVI
          else if (unos=1) then  //proverava samo desni 2
          begin
             if ( (vrh[2]-dno[2])< (k*60 / 100) ) then
              begin      //prosirujemo na racun drugog steka
                 prosirenje:=(k*20) div 100;
                    for i:=vrh[2] downto dno[2] do  //??????????????
                        stek[i+prosirenje]:=stek[i];
                    dno[2]:=dno[2]+prosirenje;
                    vrh[2]:=vrh[2]+prosirenje;
                    write('Unesite vrednost koju hocete da dodate: ');
                    readln(vrednost);
                    stek[vrh[unos]+1]:=vrednost;
                    vrh[unos]:=vrh[unos]+1;
                    q:=1;

              end
             else
              writeln('GRESKA - Stek je popujen, i ne moze se prosiriti');
          end
          else if (unos=br) then  //proverava samo levi pretposlednji br-1
          begin
             if ( (vrh[br-1]-dno[br-1])< (k*60 / 100) ) then
              begin        //prosiruje se na racun pretposlednjeg steka br-1
                 prosirenje:=(k*20) div 100;
                    for i:=dno[br] to vrh[br] do  //??????????????
                        stek[i-prosirenje]:=stek[i];
                    dno[br]:=dno[br]-prosirenje;
                    vrh[br]:=vrh[br]-prosirenje;
                    write('Unesite vrednost koju hocete da dodate: ');
                    readln(vrednost);
                    stek[vrh[unos]+1]:=vrednost;
                    vrh[unos]:=vrh[unos]+1;
                    q:=1;

              end
             else
              writeln('GRESKA - Stek je popujen, i ne moze se prosiriti.');
          end;
        end

      else if (vrh[unos]<>dno[unos+1]) and (q<>1) then // nije popunjen  i smesta vrednost na zeljeni stek
      begin
          write('Unesite vrednost koju zelite da ubacite na stek: ');
          readln(vrednost);
          stek[vrh[unos]+1]:=vrednost;
          vrh[unos]:=vrh[unos]+1;
          writeln('Uspesno ste dodali vrednost na zeljeni stek. Klikom na opciju 5 ili 6 u glavnom meniju mozete da proverite sadrzaj steka.');
      end
      else write('GRESKA - Stek je popunjen i ne moze se prosiriti.');
    end;

end;
Procedure DodajNeodredjeno(var stek,dno,vrh:niz; br:integer);  //TRECA STAVKA
var vrednost,i,dodato: integer;
begin
  write('Unesite vrednost koju zelite da dodate na stek: ');
  readln(vrednost);
  dodato:=0;
  for i:=1 to br do
   begin
     if ( (vrh[i]-dno[i])<k ) then
      begin
        stek[vrh[i]+1]:=vrednost;
        vrh[i]:=vrh[i]+1;
        dodato:=1;
      end;
     if dodato=1 then break;
   end;
  if dodato=0 then
   writeln('GRESKA - Svi stekovi su popunjeni.');
end;
Procedure UkloniOdredjeno(var stek,dno,vrh:niz; br,k:integer);                   //CETVRTA STAVKA
var i,unos:integer;
begin
  write('Unesite redni broj steka sa kog zelite da uklonite element: ');
  readln(unos);
  if (dno[unos]=vrh[unos]) then
    begin
      writeln('GRESKA - Stek je prazan.');
    end
  else
   begin
     vrh[unos]:=vrh[unos]-1;
     writeln('Uspesno ste ukloni element sa vrha zeljenog steka. Za proveru-izabrati opciju 5 ili 6 u glavnom meniju.');
   end;
end;
Procedure IspisiSve(var stek:niz; n,br:integer);  //PETA STAVKA
var i,j:integer;
begin
   for i:=1 to br do
    begin
      write('Elementi ', i, '. steka su: ');
      for j:=dno[i]+1 to vrh[i] do
       write(stek[j],' ');
      writeln();
    end;
end;
Procedure IspisiOdredjeno(var stek,dno,vrh:niz);                  //SESTA STAVKA
var i,unos:integer;
begin
  write('Unesite redni broj steka koji zelite da ispisete: ');
  readln(unos);
  if (dno[unos]=vrh[unos]) then
    begin
      writeln('Stek je prazan.');
    end
  else
  begin
    write('Elementi zeljenog steka su: ');
    for i:=dno[unos]+1 to vrh[unos] do
    write(stek[i],' ');
  end;
end;
begin //glavni program
  writeln('RAD SA STEKOVIMA');
  writeln();
  writeln();
  writeln('                         Meni');
  writeln('******************************************************************');
  writeln('1 - Stvaranje stekova');
  writeln('2 - Dodavanje celobrojne vrednosti na vrh tacno odredjenog steka');
  writeln('3 - Dodavanje celobrojne vrednosti u celu struktutu');
  writeln('4 - Uklanjanje elementa sa vrha specificnog steka');
  writeln('5 - Ispis elemenata cele strukture');
  writeln('6 - Ispis elemenata specificnog steka');
  writeln('7 - Prekid programa');
  writeln('------------------------------------------------------------------');
  write('Ukucajte redni broj zeljene opcije: ');
  readln(opcija);
  writeln('******************************************************************');

  while (opcija<>7) do
   begin
      case(opcija) of
            1: StvaranjeSteka(broj,k,duzinaSTEK,vrh,dno); //br stekova, kapacitet, duzina niza STEK,niz vrh,niz dno
            2: DodajOdredjeno(broj,k,duzinaSTEK,q,vrh,dno,stek);
            3: DodajNeodredjeno(stek,dno,vrh,broj);
            4: UkloniOdredjeno(stek,dno,vrh,broj,k);
            5: IspisiSve(stek,duzinaSTEK,broj);
            6: IspisiOdredjeno(stek,dno,vrh);
            7: exit;
      end;

        writeln();
        writeln();
        writeln();
        writeln('===================================================================');
        writeln('===================================================================');
        writeln('                         Meni');
        writeln('******************************************************************');
        writeln('1 - Stvaranje stekova');
        writeln('2 - Dodavanje celobrojne vrednosti na vrh tacno odredjenog steka');
        writeln('3 - Dodavanje celobrojne vrednosti u celu struktutu');
        writeln('4 - Uklanjanje elementa sa vrha specificnog steka');
        writeln('5 - Ispis elemenata cele strukture');
        writeln('6 - Ispis elemenata specificnog steka');
        writeln('7 - Prekid programa');
        writeln('------------------------------------------------------------------');
        write('Ukucajte redni broj zeljene opcije: ');
        readln(opcija);
        writeln('******************************************************************');
   end;
end.

