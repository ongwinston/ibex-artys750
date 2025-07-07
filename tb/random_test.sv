`include "environment.sv"

program random_test(jtag_intf intf);

  // declaraing environment instance
  environment env;

  initial begin
    // creating environment
    env = new(intf);

    // setting the repeat count
    // env.gen.repeat_count = 4;

    // calling run of env, it internally calls generator and driver main tasks
    env.run();
  end

endprogram