#' DX_runif
#'
#' @param n number of random numbers wanted
#' @param k DX explanation
#' @param s DX explanation
#' @param t DX explanation
#'
#' @return
#' @export
#'
#' @examples
#' dx_runif(10)
#' 
dx_runif <- function(n, k=47, s=1, t=1){
  seed <- sample.int(.Machine$integer.max, 1)
  .Call(`_DX_generator_rand_test`, n, seed, k)
}
