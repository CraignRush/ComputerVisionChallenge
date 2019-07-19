classdef test < matlab.unittest.TestCase
    %Test your challenge solution here using matlab unit tests
    %
    % Check if your main file 'challenge.m', 'disparity_map.m' and 
    % verify_dmap.m do not use any toolboxes.
    %
    % Check if all your required variables are set after executing 
    % the file 'challenge.m'
        
    methods (TestClassSetup)
        %challenge.m wird direkt mit dem Start des Unittest einmal
        %ausgefuehrt, die Variablen dann in einem .mat File gespeichert
        function getData(testCase)
            challenge;
            save('Challenge.mat');
            close all;
        end
    end
    
    methods (TestClassTeardown)
        %Loeschen der beim Starten erstellten .mat Datei
        function deleteData(testCase)
            delete('Challenge.mat')
        end
    end
            
    properties (TestParameter)
        %Anlegen der Testproperties
        
        exp_toolboxNames = {{'MATLAB'}};
        
        %Files die auf Toolboxen ueberprueft werden sollen
        filenames = {'challenge.m', 'disparity_map.m' 'verify_dmap.m'};
        
        %Variablen aus challegne.m, die ueberprueft werden
        varNames = {'group_number', 'members', 'mail', 'elapsed_time', 'D', 'R', 'T', 'p'};
        exp_incorrectInput = {0};
                
    end
    
    methods (Test)
        
        function check_toolboxes(testCase, exp_toolboxNames, filenames)
            
            %Testsuite, in der die Files auf Toolboxen untersucht werden
            [~, struct_test] = matlab.codetools.requiredFilesAndProducts(filenames);   
            act_toolboxNames = arrayfun(@(x) getfield(x, 'Name'), struct_test, 'UniformOutput', false);       
                                   
            testCase.verifyEqual(act_toolboxNames, exp_toolboxNames);            
        end
               
        function check_variables(testCase, varNames,exp_incorrectInput)
                   
            %Testsuite um die Variablen aus challenge.m zu untersuchen.
            %Keine Varibalen darf dabei null sein, keine Zelle unbefuellt
            if exist(varNames, 'var') == 0
                load('Challenge.mat');
               
            end
                               
            if iscell(eval(varNames)) == true
                act_input = length(eval(varNames));
            else
                act_input = eval(varNames);
            end
            testCase.verifyGreaterThan(act_input, exp_incorrectInput)                    
        end
        
        function check_psnr(testCase)
            
            %Vergleich des berechneten psnr und des psnr aus der Image
            %Processing Toolbox
            %Die Werte duerfen sich nicht um mehr als 0.1 unterscheiden
            if exist('D', 'var') == 0
                load('Challenge.mat');
                
            end
            
            act_p = verify_dmap(D,G);
            restoredefaultpath;
            
            exp_p = psnr(double(D),double(G));
            
            act_tolerance = act_p - exp_p;
            max_tolerance = 0.1;
            
            testCase.verifyLessThanOrEqual(act_tolerance, max_tolerance);
        end       
    end
end