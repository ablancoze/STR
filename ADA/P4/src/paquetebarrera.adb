package body paquetebarrera is
   -- Definir el cuerpo del objeto Barrera_t
   protected body barrera_t is

      -- Implementar el procedimiento Entrando del objeto protegido que se encargar� de incrementar el contador
      procedure entri
      is begin
         cont:=cont+1;
      end;

      -- Implementar la entrada Wait incluyendo la condici�n de paso (no han llegado a la barrera el n�mero de tareas indicado). En el c�digo, no hace nada, s�lo bloquea.
      entry wait
        when cont = nTareas
      is begin
         null;
      end;

      -- Implementar el procedimiento Resetear que pone el contador a 0
      procedure reset
      is begin
         cont:=0;
      end;

   -- Fin del objeto protegido
   end;

   -- Implementaci�n del procedimiento SincronizarEnBarrera
   procedure sincronizarEnBarrera(barrera: in out barrera_t)
   is begin

      -- Invoca al procedimiento Entrando de la barrera
      barrera.entri;

      -- Invoca a la entrada Wait de la barrera
      barrera.wait;

   -- Fin del procedimiento SincronizarEnBarrera
   end;

   -- Implementaci�n del procedimiento SincronizarEnBarrera
   procedure resetBarrera(barrera: in out barrera_t)
   is begin

      -- Invoca al procedimiento Resetear de la barrera
      barrera.reset;

   -- Fin del procedimiento ResetearBarrera
   end;
end paquetebarrera;
