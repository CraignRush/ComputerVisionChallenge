classdef test < matlab.unittest.TestCase
    %Test your challenge solution here using matlab unit tests
    %
    % Check if your main file 'challenge.m', 'disparity_map.m' and 
    % verify_dmap.m do not use any toolboxes.
    %
    % Check if all your required variables are set after executing 
    % the file 'challenge.m'
        
    properties (TestParameter)
        exp_toolboxNames = {{'MATLAB'}};
        filenames = {'challenge.m', 'disparity_map.m' 'verify_dmap.m'};
        
        varNames = {'group_number', 'members', 'mail', 'elapsed_time'};
        exp_incorrectInput = {0};
        
    end
      
    methods (Test)
        
        function check_toolboxes(testCase, exp_toolboxNames, filenames)
            [~, struct_test] = matlab.codetools.requiredFilesAndProducts(filenames);   
            act_toolboxNames = arrayfun(@(x) getfield(x, 'Name'), struct_test, 'UniformOutput', false);       
                                   
            testCase.verifyEqual(act_toolboxNames, exp_toolboxNames);            
        end
        
        
        
        function check_variables(testCase, varNames,exp_incorrectInput)
                   
            if exist(varNames, 'var') == 0
                challenge;
                close all;
            end
                               
            if iscell(eval(varNames)) == true
                act_input = length(eval(varNames));
            else
                act_input = eval(varNames);
            end
            testCase.verifyGreaterThan(act_input, exp_incorrectInput)
                     
        end
        
        function check_psnr(testCase)
            
            act_p = verify_dmap(D,G);
            exp_p = psnr(D,G);
            
            
            %To Do Toleranz mit einschließen
            testCase.verifyEqual(act_p, exp_p);

        end
        
    end
%     
%     function execute_challenge
%             challenge;
%     end

end