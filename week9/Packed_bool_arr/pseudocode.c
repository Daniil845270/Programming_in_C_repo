/* Create boolarr based on string e.g. "1100001" */
boolarr* boolarr_initstr(const char* str)
{
    if (str == NULL){
        on_error("Feeding a function with null pointer");
    }

    boolarr* ba = (boolarr*) ncalloc(1, sizeof(boolarr));

    return ba;
}

//need to write a function that converts a binarystr into a intstr and vice versa



