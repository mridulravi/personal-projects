----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:35:07 03/25/2013 
-- Design Name: 
-- Module Name:    seq_det - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;


-- defining entity
entity seq_det is
    Port ( 
		clk : in  STD_LOGIC;
      Load : in  STD_LOGIC;
      out1 : out  STD_LOGIC;
		out2 : out  STD_LOGIC_VECTOR (1 downto 0);
      input : in STD_logic_vector(7 downto 0)
		);
end seq_det;

-- defining architecture
architecture Behavioral of seq_det is
type state is (s0,s1,s2,s3,s4,s5,s7,s8,s9,s10);  -- types of states that can exist
signal p_state, n_state : state :=s0;  -- present and next state of FSM
signal in_seq : std_logic := '0';  -- input sequence bit
signal out_tmp : std_logic; -- output to check if sequence is detected or not, 1-> valid sequence detected / 0 otherwise
signal out_det : std_logic_vector( 1 downto 0 ); -- two bit output to define which sequence is detected
-- 01,	if 100100 detected 
-- 10,	if 110101 detected 
-- 11,	if 1100 detected
-- 00,   otherwise


-- declaring instantiation of shift register for parallel input serial output, 
-- so that bits can be processed one by one
-- input is loaded when load=1, and is serially transmitted when load = 0
component shift_reg is
port(  
	clk_s,load : in std_logic;            			
	parallel_input : in std_logic_vector(7 downto 0); 		
	serial_output : out std_logic
	);         				
end component;


begin
shift: shift_reg
	-- mapping shift register
	port map (
          clk_s => clk,
          load => Load,
          parallel_input => input,
          serial_output => in_seq
        );
		
-- always update output and present state on rising edge of clock
seq:process(clk)
	begin
		if rising_edge(clk) then
			if in_seq /= 'Z' then
				p_state<=n_state;
				out1<=out_tmp;
				out2<=out_det;
			end if;
		end if;
	end process;
	
	
-- main code for FSM	
-- simulated when present state or input sequence change
comb: process(p_state, in_seq)
	begin
		-- defining state transitions
		case p_state is
			
			-- when present state is s0 
			when s0 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s0 if input is 0
				if in_seq='0' then
					n_state<=s0;
				-- move to s1 if input is 1
				elsif in_seq='1' then
					n_state<=s1;
				-- stay in s0 otherwise
				else
					n_state<=s0;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
			
			-- when present state is s1 
			when s1 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s2 if input is 0
				if in_seq='0' then
					n_state<=s2;
				-- move to s7 if input is 1
				elsif in_seq='1' then
					n_state<=s7;				
				-- stay in s1 otherwise
				else
					n_state<=s1;
					out_tmp <= '0';
					out_det <= "00";	
				end if;

			-- when present state is s2
			when s2 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s3 if input is 0
				if in_seq='0' then
					n_state<=s3;
				-- move to s1 if input is 1
				elsif in_seq='1' then
					n_state<=s1;				
				-- stay in s2 otherwise
				else
					n_state<=s2;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
			
			-- when present state is s3 
			when s3 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s0 if input is 0
				if in_seq='0' then
					n_state<=s0;
				-- move to s4 if input is 1
				elsif in_seq='1' then 
					n_state<=s4;				
				-- stay in s3 otherwise
				else
					n_state<=s3;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
				
			-- when present state is s4 
			when s4 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s5 if input is 0
				if in_seq='0' then
					n_state<=s5;
				-- move to s7 if input is 1
				elsif in_seq='1' then
					n_state<=s7;				
				-- stay in s4 otherwise
				else
					n_state<=s4;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
				
			-- when present state is s5 
			when s5 =>
				-- move to s3 if input is 0
				if in_seq='0' then
					n_state<=s3;
					out_tmp <= '1';
					out_det <= "01"; -- first sequence detected
				-- move to s1 if input is 1
				elsif in_seq='1' then
					n_state<=s1;
					out_tmp <= '0';
					out_det <= "00";				
				-- stay in s5 otherwise
				else
					n_state<=s5;
					out_tmp <= '0';
					out_det <= "00";	
				end if;	
				
			-- when present state is s7 
			when s7 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s8 if input is 0
				if in_seq='0' then
					n_state<=s8;
				-- move to s7 if input is 1
				elsif in_seq='1' then
					n_state<=s7;				
				-- stay in s7 otherwise
				else
					n_state<=s7;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
				
			-- when present state is s8 
			when s8 =>
				-- move to s3 if input is 0
				if in_seq='0' then
					n_state<=s3;
					out_tmp <= '1';
					out_det <= "11"; -- third sequence detected
				-- move to s9 if input is 1
				elsif in_seq='1' then
					n_state<=s9;
					out_tmp <= '0';
					out_det <= "00";				
				-- stay in s8 otherwise
				else
					n_state<=s8;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
				
			-- when present state is s9 
			when s9 =>
				out_tmp <= '0';
				out_det <= "00";
				-- move to s10 if input is 0
				if in_seq='0' then
					n_state<=s10;
				-- move to s7 if input is 1
				elsif in_seq='1' then
					n_state<=s7;
				-- stay in s9 otherwise
				else
					n_state<=s9;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
				
			-- when present state is s10 
			when s10 =>
				-- move to s3 if input is 0
				if in_seq='0' then
					n_state<=s3;
					out_tmp <= '0';
					out_det <= "00";
				-- move to s1 if input is 1
				elsif in_seq='1' then
					n_state<=s1;
					out_tmp <= '1';
					out_det <= "10"; -- second sequence detected
				-- stay in s10 otherwise
				else
					n_state<=s10;
					out_tmp <= '0';
					out_det <= "00";	
				end if;
						
		end case;
	end process;
end Behavioral;

