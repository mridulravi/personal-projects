----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:06:01 03/06/2013 
-- Design Name: 
-- Module Name:    shift - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;




entity shift is
    Port ( In1 : in  STD_LOGIC_VECTOR (3 downto 0);				-- Input vector
			  In2 : in  integer; 								-- Number of shifts
			  dir : in STD_LOGIC;								-- Left(1) or right(0) shift
           Out1 : out  STD_LOGIC_VECTOR (3 downto 0));			-- final output vector after shifting
end shift;

architecture Behavioral of shift is

begin

process(In1,dir)
variable buffer1 :STD_LOGIC_VECTOR (3 downto 0);				-- a buffer that vector the output at every stage of iteration
begin
	buffer1(0):=In1(0);
	buffer1(1):=In1(1);
	buffer1(2):=In1(2);
	buffer1(3):=In1(3);
-- Code for Left Shift
-- Appends Zeros at the right
-- and puts them into a temporary buffer 
if(dir = '1') then
for i in 1 to IN2 loop
	buffer1(3):=buffer1(2);
	buffer1(2):=buffer1(1);
	buffer1(1):=buffer1(0);
	buffer1(0):='0';
end loop;
else 

-- Code for Right Shift
-- Appends Zeros on the left
-- and puts them into a temporary buffer 
for i in 1 to IN2 loop
	buffer1(0):=buffer1(1);
	buffer1(1):=buffer1(2);
	buffer1(2):=buffer1(3);
	buffer1(3):='0';
end loop;
end if;
--Output the shifted vector
	Out1(0)<=buffer1(0);
	Out1(1)<=buffer1(1);
	Out1(2)<=buffer1(2);
	Out1(3)<=buffer1(3);
end process;
 
end Behavioral;

